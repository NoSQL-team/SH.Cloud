//
// Created by lerakry on 12.11.2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "ServerQueue.h"

class MockServerQueue : public tcp_server::ServerQueue {
    MockServerQueue();
    MOCK_METHOD0(SendRequest, std::string());
    MOCK_METHOD1(AddRequest, void(std::string));
};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

