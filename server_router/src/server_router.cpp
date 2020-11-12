//
// Created by Andrew Kireev on 06.11.2020.
//

#include "server_interface.h"
#include "server_router.h"

namespace tcp_network {

    ServerRouter::ServerRouter(const std::string& ip, uint16_t port) {}

    ServerRouter::~ServerRouter() noexcept {}

    RequestDestination ServerRouter::build_rout(std::string& request) {
        return RequestDestination::FRIEND_SERV;
    }
}