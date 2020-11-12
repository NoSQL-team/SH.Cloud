//
// Created by Andrew Kireev on 08.11.2020.
//

#ifndef NOSKOOL_SERVER_ROUTER_H
#define NOSKOOL_SERVER_ROUTER_H

#include "server_interface.h"

#include <unordered_map>
#include <string>

namespace tcp_network {

    class ServerRouter : public IServer {
    public:
        ServerRouter() = default;

        ServerRouter(const std::string& ip, uint16_t port);

        ~ServerRouter() noexcept;

        RequestDestination build_rout(std::string& request);

    private:

    };
}

#endif //NOSKOOL_SERVER_ROUTER_H
