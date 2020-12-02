//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_UTILTY_H
#define NOSKOOL_UTILTY_H

#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace tcp_network {

    enum RequestDestination {
        FRIEND_SERV,
        POST_SERV,
        AUTH_SERV,
        USER_SERV
    };

    struct Destination {
    	std::string ip;
		uint16_t port;
    };

    class ParseJson {
    public:

        ParseJson() = default;

        RequestDestination get_destination(std::string& request);

        std::map<std::string, std::string> parse(std::string& request);

		std::map<std::string, std::string> print(boost::property_tree::ptree const& pt)
		{
			std::map<std::string, std::string> requst;
			using boost::property_tree::ptree;
			ptree::const_iterator end = pt.end();
			for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
//				std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
				requst.insert({std::string(it->first), it->second.get_value<std::string>()});
//				print(it->second);
			}
			return requst;
		}

    };
}

#endif //NOSKOOL_UTILTY_H
