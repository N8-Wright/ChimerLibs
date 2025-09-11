#include "Chimer.Logging/ConsoleLogger.hpp"
#include "Chimer.IO/IOCompletion.hpp"
#include "Chimer.IO/Socket.hpp"
#include "Chimer.IO/IOContext.hpp"

#include <stop_token>

using namespace Chimer::IO;
using namespace Chimer::Logging;
std::string buffer;
static std::stop_source stopSource;

class HelloWorldConnection
{
    Socket m_clientSocket;
    std::shared_ptr<Logger> m_logger;
    std::string m_buffer;

public:
    HelloWorldConnection(Socket clientSocket, std::shared_ptr<Logger> logger)
        : m_clientSocket(std::move(clientSocket)), m_logger(std::move(logger))
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

int main(const int, const char**)
{
    buffer.resize(1024);
    const auto logger = std::make_shared<ConsoleLogger>(LogLevel::Info);
    std::vector<HelloWorldConnection> connections;

    try
    {
        IOContext context;
        IOCompletion runner(logger);
        const auto listener = Socket::CreateTcpSocket();
        runner.Add(listener);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9000);
        addr.sin_addr.s_addr = INADDR_ANY;

        listener.Bind(addr);
        listener.Listen();

        auto client = Socket::CreateTcpSocket();
        listener.Accept(client, [&]() {
            runner.Add(client);
            connections.emplace_back(std::move(client), logger);

            auto& connection = connections.back();
            client = Socket::CreateTcpSocket();
            connection.Read();
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        runner.Run(stopSource.get_token());
    }
    catch (const std::exception& e)
    {
        logger->Log(LogLevel::Error, e.what());
    }

    return 0;
}