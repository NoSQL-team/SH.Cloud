//
// Created by Andrew Kireev on 12.11.2020.
//

#include "utilty.h"
#include <map>

namespace tcp_network {

    RequestDestination ParseJson::get_destination(std::string& request) {
        return RequestDestination::POST_SERV;
    }

    std::map<std::string, std::string> ParseJson::parse(std::string& request) {

        return {{"fdsfds", "fdsfdsa"}};
    }

}
