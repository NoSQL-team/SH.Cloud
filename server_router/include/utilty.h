//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_UTILTY_H
#define NOSKOOL_UTILTY_H

#include <string>
#include <map>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace tcp_network {

    enum class RequestDestination {
        FRIEND_SERV,
        POST_SERV,
        AUTH_SERV,
        USER_SERV,
        UNKNOWN
    };

    void print_destination(RequestDestination destination);

    struct Destination {
    	std::string ip;
		uint16_t port;
    };

    class ParseJson {
    public:

        ParseJson() = default;

        static RequestDestination get_destination(std::string& request);

        static std::map<std::string, std::string> parse(std::string& request);
    };
}

#endif //NOSKOOL_UTILTY_H
