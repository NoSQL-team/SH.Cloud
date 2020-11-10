//
// Created by Andrew Kireev on 08.11.2020.
//


#include "mock_classes.h"
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>



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

// Тест парсера Json

TEST_F(TestParseJson, test_parsing_destination) {
    EXPECT_EQ("123423",json_parser->get_destination(request));
}

TEST_F(TestParseJson, test_parsing) {
    EXPECT_EQ(result,json_parser->parse(request));
}

TEST_F(TestParseJson, test_getting_request) {
    EXPECT_EQ(result,json_parser->get_request());
}


TEST(Server_friends, test_reading_from_client) {
    MockServerFriends server("127.0.0.1", 1234);

    EXPECT_CALL(server, create_epoll()).Times(1);
}

void echo_serv_for_connection(int* serv_sock, int* listen_sock) {
    MockServerFriends server("127.0.0.1", 1234);

    struct sockaddr_in local;

    *serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);

    local.sin_family = AF_INET;

    bind(*serv_sock, (struct sockaddr *)&local, sizeof(local));


    listen(*serv_sock, 5);

    *listen_sock = accept(*serv_sock, NULL, NULL);
}

TEST(Connection, test_connection_write) {
    int serv_sock, listen_sock;

    echo_serv_for_connection(&serv_sock, &listen_sock);

    tcp_network::Connection connection("127.0.0.1", 1234);
    connection.send_size(sizeof("hello"));
    connection.write("hello");

    char buf[6];
    char number[20];

    read(listen_sock, number, sizeof(size_t));
    int size = atoi(number);
    read(listen_sock, buf, size);
    close(listen_sock);
    close(serv_sock);
    EXPECT_EQ(true, strcmp("hello", buf));
}

TEST(Server_friends, test_writing_to_server) {
    MockServerFriends server("127.0.0.1", 1234);

    EXPECT_CALL(server, handle_client(testing::_, testing::_)).Times(1);
    server.event_loop();

    tcp_network::Connection connection("127.0.0.1", 1234);
    connection.send_size(sizeof("hello"));
    connection.write("hello");
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}