//
// Created by Andrew Kireev on 10.11.2020.
//

#ifndef TESTS_MOCK_CLASSES_H
#define TESTS_MOCK_CLASSES_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "server_interface.h"
#include <memory>
#include "utilty.h"
#include "friends_data_base.h"
#include "server_friends.h"

class MockSocket : public FriendsDataBase {
public:
    MockSocket() = default;
    MOCK_METHOD0(close, void());
};


class MockFriendsDataBase : public FriendsDataBase {
public:
    MockFriendsDataBase(){}
    MOCK_METHOD1(insert, void(std::map<std::string, std::string> request));
    MOCK_METHOD1(select, std::string(std::map<std::string, std::string>& request));
    MOCK_METHOD0(update, void());
};

class MockServerFriends : public tcp_network::ServerFriends {
public:
    MockServerFriends() {}
    MockServerFriends(const std::string& ip, uint16_t port) :
    tcp_network::ServerFriends(ip, port)
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
};

class MockConnection : public tcp_network::Connection {
public:
    MockConnection(std::string& ip, uint16_t port) :
    tcp_network::Connection(ip, port) {}
    MOCK_METHOD1(write, size_t(const std::string& message));
    MOCK_METHOD1(read, size_t(const std::string& message));
    MOCK_METHOD0(close, void());
    MOCK_CONST_METHOD0(is_opened, bool());
    MOCK_METHOD2(connect, void(const std::string& addr, uint16_t port));
    MOCK_METHOD1(send_size, void(const size_t data));
    MOCK_METHOD0(recv_size, size_t());
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
    int fd = 4;

    tcp_network::Socket socket_ = tcp_network::Socket(fd);
};

class TestParseJson : public ::testing::Test {
protected:
    void SetUp() {
        json_parser = std::make_unique<tcp_network::ParseJson>();
    }

    void TearDown() {
        json_parser.reset();
    }
    std::unique_ptr<tcp_network::ParseJson> json_parser;
    std::string request = "123423\ncreate/\n{\"username\": \"Filechka322\",\n\"email\":"
                          "\"UUU@gmail.com\",\"password\": \"qwerty\"}";
    std::map<std::string, std::string> result =
            {{"username", "Filechka322"}, {"email", "UUU@gmail.com"},
             {"password", "qwerty"}};
};

#endif //TESTS_MOCK_CLASSES_H
