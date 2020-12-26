//
// Created by lerakrya on 09.12.2020.
//

#include "Server.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try {
        Server(12012);
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}