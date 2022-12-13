#include <iostream>
#include "Server.h"
#include <string>

int main() {
    Server* server = new Server();
    try
    {
        server->run();
        std::string input = "";
        while (input != "EXIT")
        {
            std::cin >> input;
        }
        delete server;
    }
    catch (...)
    {
        std::cout << "an exception has been thrown" << std::endl;
        delete server;
        exit(1);
    }
    return 0;

}
