//
// Created by lerakry on 12.11.2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ServerUser.h>

#include "SServer.h"

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
public:
    MockSocket() = default;
    MockSocket(const int fd) : Socket(fd) {}
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(get_socket, int());
};

class MockSServer : public tcp_server::SServer {
public:
    MockSServer(const std::string& ip, const uint16_t port) : tcp_server::SServer(ip, port) {}
    MOCK_METHOD2(open, void(const std::string& ip, uint16_t port));
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(accept, tcp_server::Connection());
    MOCK_METHOD2(client, void(tcp_server::Socket& socket, uint16_t port));
    MOCK_METHOD1(erase_connection, void(tcp_server::Connection& connection));
};


class MockServUser : public tcp_server::ServerUser {
public:
    MockServUser(const std::string& ip, const uint16_t port) : tcp_server::ServerUser(ip, port) {}
    MOCK_METHOD2(open, void(const std::string& ip, uint16_t port));
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(accept, tcp_server::Connection());
    MOCK_METHOD2(client, void(tcp_server::Socket& socket, uint16_t port));
    MOCK_METHOD1(erase_connection, void(tcp_server::Connection& connection));
    MOCK_METHOD0(AllUsers, std::string());
};



TEST(MockSocket, test_creating_connection) {
    MockSocket socket;
    EXPECT_CALL(socket, close()).Times(1);

    tcp_server::Connection con(socket);
    con.close();
}


TEST(MockSServer, testing_use_of_db) {
    uint16_t port = 1234;
    std::string ip = "127.0.0.1";
    MockServUser serv(ip, port);

    EXPECT_CALL(serv, AllUsers()).Times(testing::AtLeast(1));


    tcp_server::Connection con(ip, port);

    con.connect(ip, port);
    con.write("12321/get_all_users");
}


TEST(MockSServer, testing_delete_from_db) {
    uint16_t port = 1234;
    std::string ip = "127.0.0.1";
    MockServUser serv(ip, port);

    EXPECT_CALL(serv, AllUsers()).Times(testing::AtLeast(1));


    tcp_server::Connection con(ip, port);

    con.connect(ip, port);
    con.write("12321/\ndelete_user\n {'id': '3232'}");
}


TEST(MockSServer, get_user_data) {
    uint16_t port = 1234;
    std::string ip = "127.0.0.1";
    MockServUser serv(ip, port);

    EXPECT_CALL(serv, AllUsers()).Times(testing::AtLeast(1));


    tcp_server::Connection con(ip, port);

    con.connect(ip, port);
    con.write("12321/\nget_user_data_user\n {'id': '3232'}");
}


TEST(MockSServer, create_new_user) {
    uint16_t port = 1234;
    std::string ip = "127.0.0.1";
    MockServUser serv(ip, port);

    EXPECT_CALL(serv, AllUsers()).Times(testing::AtLeast(1));


    tcp_server::Connection con(ip, port);

    con.connect(ip, port);
    con.write("12321/\ncreate_userr\n {'name': 'Anton',"
              "'login': 'filechka_antonov_ura_ura',"
              "'email': 'ia_anton@mail.ru'}");
}

TEST(Parser, parse_json) {
    Parser parser;
    std::string  requst = "12321/\ncreate_userr\n {'name': 'Anton',"
                      "'login': 'filechka_antonov_ura_ura',"
                      "'email': 'ia_anton@mail.ru'}";

    std::map<std::string, std::string> result = {{"name", "Anton"},
            {"login", "filechka_antonov_ura_ura"},
            {"email", "ia_anton@mail.ru"}};

    EXPECT_EQ(result, parser.parsejson(requst));

    EXPECT_EQ(result, parser.get_string());
}





int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}