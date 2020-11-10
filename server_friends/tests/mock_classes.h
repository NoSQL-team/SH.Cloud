//
// Created by Andrew Kireev on 10.11.2020.
//

#ifndef TESTS_MOCK_CLASSES_H
#define TESTS_MOCK_CLASSES_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <server_interface.h>
#include "utilty.h"
#include "friends_data_base.h"


class MockFriendsDataBase : public FriendsDataBase{
public:
    MOCK_METHOD0(insert, void());
    MOCK_METHOD0(select, void());
    MOCK_METHOD0(update, void());
};

class MockServerFriends : public tcp_network::IServer {
public:
    MockServerFriends(const std::string& ip, uint16_t port) :
    tcp_network::IServer(ip, port);
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(accept, tcp_network::Connection());
    MOCK_METHOD2(open, void(const std::string& ip, int port));
    MOCK_METHOD0(create_epoll, void());
    MOCK_METHOD2(add_epoll, void(int fd,  uint32_t events));
    MOCK_METHOD0(event_loop, void());
    MOCK_METHOD0(accept_clients, void());
    MOCK_METHOD2(handle_client, void(int fd, uint32_t event));
    MOCK_METHOD0(close_epoll, void());
    MOCK_METHOD1(erase_connection, void(const tcp_network::Connection& con));
    MOCK_METHOD2(modify_epoll, void(int fd, uint32_t events));
};

class MockConnection : public tcp_network::Connection {
public:
    MOCK_METHOD1(write, size_t(const std::string& message));
    MOCK_METHOD1(read, size_t(const std::string& message));
    MOCK_METHOD0(close, void());
    MOCK_CONST_METHOD0(is_opened, bool());
    MOCK_METHOD2(connect, void(const std::string& addr, uint16_t port));
    MOCK_METHOD1(send_size, void(const size_t data));
    MOCK_METHOD1(recv_size, void(const size_t data));
    MOCK_METHOD1(set_serv_name, void(const std::string& serv_name));
    MOCK_METHOD0(get_serv_name, std::string());
    MOCK_METHOD0(get_con, int());
};


class TestSocket : public ::testing::Test {
protected:
    void SetUp() {
    }

    void TearDown() {

    }
    tcp_network::Socket socket_ = tcp_network::Socket(4);
};

#endif //TESTS_MOCK_CLASSES_H