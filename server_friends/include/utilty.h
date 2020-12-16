//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_UTILTY_H
#define NOSKOOL_UTILTY_H

#include <map>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/basic_logger.hpp>

namespace tcp_network {

	enum class RequestDestination {
		FRIEND_SERV,
		POST_SERV,
		AUTH_SERV,
		USER_SERV,
		HTTP_SERV,
		UNKNOWN
	};

	void print_destination(RequestDestination destination);

	struct Destination {
		std::string ip;
		uint16_t port;
	};

	class ParseJson {
	public:
		ParseJson();

		static RequestDestination get_destination(std::string& request);

		static std::map<std::string, std::string> parse(std::string& request);
	};
}

#endif //NOSKOOL_UTILTY_H
