//
// Created by lerakry on 12.11.2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SServer.h"

//using ::testing::tcp_server

class MockConnection : public tcp_server::Connection {
public:
    MockConnection() {}
    MockConnection(std::string& ip, const uint16_t port) : Connection(ip, port) {}
    MOCK_METHOD1(write, size_t(const std::string& data));
    MOCK_METHOD1(read, size_t(std::string& data));
    MOCK_METHOD0(close, void());
    MOCK_METHOD1(set_time_out, void(int time));
    MOCK_METHOD0(is_opened, bool());
    MOCK_METHOD2(connect, void(std::string& addr, uint16_t port));
    MOCK_METHOD0(get_connection, int());
};

class MockSocket : public tcp_server::Socket {
    MockSocket() = default;
    MockSocket(const int fd) : Socket(fd) {}
    MOCK_METHOD0(clode, void());
    MOCK_METHOD0(get_socket, int());
};

class MockSServer : public tcp_server::SServer {
    MockSServer(const std::string& ip, const uint16_t port) : tcp_server::SServer(ip, port) {}
    MOCK_METHOD2(open, void(const std::string& ip, uint16_t port));
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(accept, tcp_server::Connection());
    MOCK_METHOD2(client, void(tcp_server::Socket& socket, uint16_t port));
    MOCK_METHOD1(erase_connection, void(tcp_server::Connection& connection));
};



TEST(SServer, test_creating_connection) {
    MockSocket socket();

    EXPECT_CALL(socket, close).Times(testing::AtLeast(1));
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}