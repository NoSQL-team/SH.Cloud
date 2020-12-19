#include <iostream>

#include <boost/property_tree/ini_parser.hpp>

#include "Server.h"


int main() {
    try
    {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("../queue_settings.ini", pt);
        Server s(pt.get<int>("queue.port"));
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
