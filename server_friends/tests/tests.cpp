//
// Created by Andrew Kireev on 08.11.2020.
//


#include "mock_classes.h"
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>



TEST_F(TestSocket, Socket_RAII) {
    ASSERT_TRUE(true);
    EXPECT_EQ(4, socket_.get());
}

TEST_F(TestSocket, test_socket_close) {
    ASSERT_TRUE(true);
    socket_.close();
    EXPECT_EQ(-1, socket_.get());
}


//TEST(test_soket, close) {
//    MockSocket socket;
//
//    EXPECT_CALL(socket, close()).Times(1);
//
//    tcp_network::Connection con(socket);
//    con.close();
//}

// Тест парсера Json

TEST_F(TestParseJson, test_parsing_destination) {
    ASSERT_TRUE(true);
    std::string request = "fsfds";
    tcp_network::ParseJson json_parser;
    EXPECT_EQ(tcp_network::RequestDestination::POST_SERV,json_parser.get_destination(request));
}

TEST_F(TestParseJson, test_parsing) {
    ASSERT_TRUE(true);
    EXPECT_EQ(result,json_parser->parse(request));
}

TEST_F(TestParseJson, test_getting_request) {
    ASSERT_TRUE(true);
    EXPECT_EQ(result,json_parser->get_request());
}


TEST(Databasetest, data_base) {
    MockFriendsDataBase dataBase;
    ASSERT_TRUE(true);

    std::map<std::string, std::string> user = {{"id", "Anton1"},
                                               {"id2", "Anton2"}};

    EXPECT_CALL(dataBase, insert(user)).Times(1);

    MockServerFriends server;

    server.open("127.0.0.1", 1234);
    server.event_loop();

    uint16_t port = 1234;
    std::string ip = "127.0.0.1";
    EXPECT_CALL(server, handle_client(testing::_,
                                    testing::_)).Times(testing::AtLeast(1));
    tcp_network::Connection con(ip, port);

    std::string request = "1234230\ncreate/\n{'username': 'Filechka322','email':"
                          "'UUU@gmail.com','password': 'qwerty'}";
    con.send_size(sizeof(request));
    con.write(request);
}




TEST(MockServerFriends, test_reading_from_client) {
    ASSERT_TRUE(true);
    MockServerFriends server("127.0.0.1", 1234);

    EXPECT_CALL(server, create_epoll()).Times(1);
}

TEST(Server_friends, test_writing_to_server) {
    ASSERT_TRUE(true);
    MockServerFriends server("127.0.0.1", 1234);

    EXPECT_CALL(server, handle_client(testing::_, testing::_)).Times(1);
    server.event_loop();

    tcp_network::Connection connection;
    connection.send_size(sizeof("hello"));
    connection.write("hello");
}


void echo_serv_for_connection(int* serv_sock, int* listen_sock) {
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
    ASSERT_TRUE(true);
    int serv_sock, listen_sock;

    echo_serv_for_connection(&serv_sock, &listen_sock);

    uint16_t port = 1234;
    std::string ip = "127.0.0.1";
    tcp_network::Connection connection(ip, port);
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

TEST(test_function_calling, ServerFrineds) {
    ASSERT_TRUE(true);
    uint16_t port = 1234;
    std::string ip = "127.0.0.1";
    MockServerFriends serv(ip, port);

    EXPECT_CALL(serv, create_epoll()).Times(testing::AtLeast(1));
    EXPECT_CALL(serv, add_epoll(testing::_,
            testing::_)).Times(testing::AtLeast(1));

    EXPECT_CALL(serv, handle_client(testing::_,
                                    testing::_)).Times(testing::AtLeast(1));

    serv.event_loop();

    tcp_network::Connection con(ip, port);
    con.send_size(sizeof("hello"));
    con.write("hello");
    con.close();
    serv.close();
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}