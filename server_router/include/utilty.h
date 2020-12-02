//
// Created by Andrew Kireev on 02.11.2020.
//

#ifndef NOSKOOL_UTILTY_H
#define NOSKOOL_UTILTY_H

#include <string>
#include <map>
#include <unordered_map>

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

    };
}

#endif //NOSKOOL_UTILTY_H
