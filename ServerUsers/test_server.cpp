//
// Created by lerakrya on 09.12.2020.
//

#include "Server.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "hello";
    try
    {
            Server(8082);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}