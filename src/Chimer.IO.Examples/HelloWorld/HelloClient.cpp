#include "Chimer.IO/Socket.hpp"
#include "Chimer.IO/IOCompletion.hpp"
#include "Chimer.IO/IOContext.hpp"
#include "Chimer.Logging/ConsoleLogger.hpp"

#include <iostream>

using namespace Chimer::IO;
using namespace Chimer::Logging;

std::stop_source stopSource;

int main()
{
    const auto logger = std::make_shared<ConsoleLogger>(LogLevel::Info);

    try
    {
        IOContext context;
        IOCompletion runner(logger);

        const Socket clientSocket(SocketFamily::Inet, SocketType::Stream);
        clientSocket.Connect("127.0.0.1", "9000", SocketType::Stream);
        runner.Add(clientSocket);

        std::string message = "Hello, world";
        clientSocket.Write(message, [&message](size_t bytesWritten) {
            std::cout << "Wrote " << message << std::endl;
            stopSource.request_stop();
        });

        runner.Run(stopSource.get_token());
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}