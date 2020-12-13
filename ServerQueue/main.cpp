#include <iostream>
#include "project/includes/Server.h"
int main() {

    std::cout << "hello";
    try
    {

//        boost::asio::io_service io_service;

        Server s(8082);

//        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
