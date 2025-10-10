#include "Chimer/Logging/ConsoleLogger.hpp"
#include "Chimer/IO/IOCompletion.hpp"
#include "Chimer/IO/Socket.hpp"
#include "Chimer/IO/IOContext.hpp"

#include <stop_token>

using namespace Chimer::IO;
using namespace Chimer::Logging;

class HelloWorldConnection
{
    Socket m_clientSocket;
    std::shared_ptr<Logger> m_logger;
    std::string m_buffer;

public:
    HelloWorldConnection(Socket clientSocket, std::shared_ptr<Logger> logger) :
        m_clientSocket(std::move(clientSocket)), m_logger(std::move(logger))
    {
        m_buffer.resize(1024);
    }

    void OnRead(const std::size_t bytesRead)
    {
        if (bytesRead > 0)
        {
            const std::string_view message(m_buffer.data(), bytesRead);
            m_logger->Log(LogLevel::Info, std::string("Received message: ") + std::string(message));
            Read();
        }
        else
        {
            m_logger->Log(LogLevel::Info, "Received EOF. Closing socket");
            m_clientSocket.~Socket();
        }
    }

    void Read()
    {
        m_clientSocket.Read(m_buffer, [this](const auto bytesRead) {
            OnRead(bytesRead);
        });
    }
};

std::stop_source stopSource;
Socket client;

void AcceptConnections(const IOCompletion& runner,
                       const Socket& listener,
                       std::vector<HelloWorldConnection>& connections,
                       std::shared_ptr<Logger> logger,
                       const std::stop_token& stopToken)
{
    if (stopToken.stop_requested())
    {
        return;
    }

    client = Socket(SocketFamily::Inet, SocketType::Stream);
    listener.Accept(client, [&, logger]() {
        runner.Add(client);
        connections.emplace_back(std::move(client), logger);

        auto& connection = connections.back();
        connection.Read();
        AcceptConnections(runner, listener, connections, logger, stopToken);
    });
}

int main(const int, const char**)
{
    const auto logger = std::make_shared<ConsoleLogger>(LogLevel::Info);

    try
    {
        std::vector<HelloWorldConnection> connections;
        IOContext context;
        IOCompletion runner(logger);

        const auto listener = Socket(SocketFamily::Inet, SocketType::Stream);
        runner.Add(listener);
        listener.Bind(std::nullopt, "9000", SocketFamily::Inet, SocketType::Stream);
        listener.Listen();

        AcceptConnections(runner, listener, connections, logger, stopSource.get_token());
        runner.Run(stopSource.get_token());
    }
    catch (const std::exception& e)
    {
        logger->Log(LogLevel::Error, e.what());
    }

    return 0;
}