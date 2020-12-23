//
// Created by Andrew Kireev on 03.12.2020.
//

#include <iostream>

#include <boost/property_tree/ini_parser.hpp>

#include "server_friends.h"



using namespace boost;
using namespace boost::system;
using namespace boost::asio;


int main(int argc, char *argv[]) {
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("../friends_settings.ini", pt);
		std::map<std::string, std::string> db_settings = {{"dbname",pt.get<std::string>("db.dbname")},
															{"host", pt.get<std::string>("db.host")},
															{"user", pt.get<std::string>("db.user")},
															{"password", pt.get<std::string>("db.password")}};

		tcp_network::Server s(pt.get<int>("friends.port"), db_settings);

	}
	catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}