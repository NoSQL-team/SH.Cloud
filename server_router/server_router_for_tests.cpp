//
// Created by Andrew Kireev on 30.11.2020.
//

#include <iostream>
#include <memory>
#include <boost/property_tree/ini_parser.hpp>

#include "server_router.h"


using namespace boost;
using namespace boost::system;
using namespace boost::asio;


int main(int argc, char *argv[]) {
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("../router_settings.ini", pt);
		tcp_network::Server s(pt.get<int>("router.port"));
	}
	catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}