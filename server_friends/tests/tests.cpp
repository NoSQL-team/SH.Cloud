//
// Created by Andrew Kireev on 08.11.2020.
//


#include "mock_classes.h"



TEST_F(TestSocket, Socket_RAII) {
    EXPECT_EQ(4, socket_.get());
}

TEST_F(TestSocket, test_socket_close) {
    socket_.close();
    EXPECT_EQ(-1, socket_.get());
}

TEST_F(TestSocket, test_socket_destructro) {
    int sock_fd  = 5;

    {
        tcp_network::Socket sock(sock_fd);
}

    EXPECT_EQ(-1, sock_fd);
}


TEST(Server_friends, test_reading_from_client) {
    MockServerFriends server("127.0.0.1", 8081);

    EXPECT_CALL(server, create_epoll()).Times(1);
}

TEST(Server_friends, test_writing_to_server) {
    MockServerFriends server("127.0.0.1", 8081);

    EXPECT_CALL(server, handle_client(testing::_, testing::_)).Times(1);
    server.event_loop();

    tcp_network::Connection connection("127.0.0.1", 8081);
    connection.send_size(sizeof("hello"));
    connection.write("hello");
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}