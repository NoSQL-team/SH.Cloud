//
// Created by Andrew Kireev on 12.11.2020.
//

#ifndef TESTS_MOCK_CLASSES_H
#define TESTS_MOCK_CLASSES_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <server_interface.h>
#include <memory>
#include "utilty.h"
#include "server_router.h"


class MockServerRouter : public tcp_network::ServerRouter {
public:
    MockServerRouter() {}
    MockServerRouter(const std::string& ip, uint16_t port) :
            tcp_network::ServerRouter(ip, port)
    {}
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(accept, tcp_network::Connection());
    MOCK_METHOD2(open, void(const std::string& ip, uint16_t port));
    MOCK_METHOD0(create_epoll, void());
    MOCK_METHOD2(add_epoll, void(tcp_network::Socket& fd,  uint32_t events));
    MOCK_METHOD0(event_loop, void());
    MOCK_METHOD0(accept_clients, void());
    MOCK_METHOD2(handle_client, void(tcp_network::Socket& fd, uint32_t event));
    MOCK_METHOD0(close_epoll, void());
    MOCK_METHOD1(erase_connection, void(const tcp_network::Connection& con));
    MOCK_METHOD2(modify_epoll, void(tcp_network::Socket& fd, uint32_t events));
    MOCK_METHOD1(build_rout, tcp_network::RequestDestination(std::string& request));
};

#endif //TESTS_MOCK_CLASSES_H
