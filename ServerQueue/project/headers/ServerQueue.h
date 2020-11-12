//
// Created by lerakry on 12.11.2020.
//

#ifndef SERVERQUEUE_SERVERQUEUE_H
#define SERVERQUEUE_SERVERQUEUE_H

#include <queue>

#include "SServer.h"

namespace tcp_server {

    class ServerQueue : public SServer {
    public:
        ServerQueue(const std::string &ip, uint16_t port);

        ~ServerQueue() noexcept;

        std::string SendRequest();

        void AddRequest(std::string);

    private:
        std::queue <std::string> request_queue;
    };
}

#endif //SERVERQUEUE_SERVERQUEUE_H
