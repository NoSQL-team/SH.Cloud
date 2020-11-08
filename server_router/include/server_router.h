//
// Created by Andrew Kireev on 08.11.2020.
//

#ifndef NOSKOOL_SERVER_ROUTER_H
#define NOSKOOL_SERVER_ROUTER_H

#include "connection.h"

#include <unordered_map>
#include <string>

namespace tcp_network {

    class ServerRouter : public IServer {
    public:
        ServerRouter(const std::string& ip, uint16_t port);

        ~ServerRouter() noexcept;

        RequestDestination choose_server()

    private:

    };
}

#endif //NOSKOOL_SERVER_ROUTER_H
