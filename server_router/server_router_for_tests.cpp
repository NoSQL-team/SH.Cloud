//
// Created by Andrew Kireev on 30.11.2020.
//

#include <iostream>
#include <memory>
#include <boost/property_tree/ini_parser.hpp>
//#include <boost/log/trivial.hpp>

#include "server_router.h"


using namespace boost;
using namespace boost::system;
using namespace boost::asio;


int main() {
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("../router_settings.ini", pt);
		tcp_network::Server s(pt.get<int>("router.port"));
//		tcp_network::Server s(8042);
	}
	catch (std::exception& e) {
//		BOOST_LOG_TRIVIAL(error) << e.what();
	}

	return 0;
}