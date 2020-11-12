//
// Created by lerakry on 12.11.2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "ServerQueue.h"

class MockServerQueue : public tcp_server::ServerQueue {
public:
    MockServerQueue() {}
    MockServerQueue(const std::string &ip, uint16_t port) :
    tcp_server::ServerQueue(ip, port) {}
    MOCK_METHOD0(SendRequest, std::string());
    MOCK_METHOD1(AddRequest, void(std::string));
};


TEST(MockServerQueue, add_new_request) {
    uint16_t port = 1234;
    std::string ip = "127.0.0.1";

    MockServerQueue server(ip, port);

    tcp_server::Connection con(ip, port);

    con.connect(ip, port);
    con.write("12321/get_all_users");

    EXPECT_CALL(server, AddRequest(testing::_)).Times(1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

