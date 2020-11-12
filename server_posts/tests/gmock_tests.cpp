//
// Created by amartery on 08.11.2020.
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "server_posts_interface.h"
#include "utility.h"
#include "posts_data_base.h"
#include "server_posts.h"

#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>


class MockSocket : public PostsDataBase {
public:
    MockSocket() = default;
    MOCK_METHOD0(close, void());
};


class MockPostsDataBase : public PostsDataBase {
public:
    MockPostsDataBase(){}
    MOCK_METHOD1(insert, void(std::map<std::string, std::string> request));
    MOCK_METHOD1(select, std::string(std::map<std::string, std::string>& request));
    MOCK_METHOD0(update, void());
};

class MockServerPosts : public tcp_server::ServerPosts {
public:
    MockServerPosts() {}
    MockServerPosts(const std::string& ip, uint16_t port) :
    tcp_server::ServerPosts(ip, port) {}
    MOCK_METHOD0(close, void());
    MOCK_METHOD0(accept, tcp_network::Connection());
    MOCK_METHOD2(open, void(const std::string& ip, uint16_t port));
    MOCK_METHOD0(set_max_connection, void(int num_connections));
    
};

class MockConnection : public tcp_server::Connection {
public:
    MockConnection(std::string& ip, uint16_t port) :
    tcp_server::Connection(ip, port) {}
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
    void SetUp() {}
    void TearDown() {}
    int fd = 4;
    tcp_server::Socket socket_ = tcp_server::Socket(fd);
};

class TestJsonParser : public ::testing::Test {
protected:
    void SetUp() {
        json_parser = std::make_unique<tcp_server::JsonParser>();
    }

    void TearDown() {
        json_parser.reset();
    }
    std::unique_ptr<tcp_server::JsonParser> json_parser;
    std::string request = "123\ncreate/\n{\"username\": \"test123\",\n\"email\":"
                          "\"test@gmail.com\",\"password\": \"test\"}";
    std::map<std::string, std::string> result =
            {
                {"username", "test123"}, 
                {"email", "test@gmail.com"},
                {"password", "test"}
            };
};


// тест класса Socket
TEST_F(TestSocket, Socket) {
    ASSERT_TRUE(true);
    EXPECT_EQ(4, socket_.get());
}

TEST_F(TestSocket, test_socket_close) {
    ASSERT_TRUE(true);
    socket_.close();
    EXPECT_EQ(-1, socket_.get());
}

// тест класса JsonParser
TEST_F(TestJsonParser, test_parsing_destination) {
    ASSERT_TRUE(true);
    std::string request = "fsfds";
    tcp_server::JsonParser json_parser;
    EXPECT_EQ(tcp_server::RequestDestination::POST_SERV,json_parser.get_destination(request));
}

TEST_F(TestJsonParser, test_parsing) {
    ASSERT_TRUE(true);
    EXPECT_EQ(result,json_parser->parse(request));
}

TEST_F(TestJsonParser, test_getting_request) {
    ASSERT_TRUE(true);
    EXPECT_EQ(result,json_parser->get_request());
}

// TODO: написать тесты для  работы с БД

// тест класса ServerFriends
TEST(MockServerFriends, test_reading_from_client) {
    ASSERT_TRUE(true);
    MockServerPosts server("127.0.0.1", 1234);
}

TEST(Server_friends, test_writing_to_server) {
    ASSERT_TRUE(true);
    MockServerPosts server("127.0.0.1", 1234);

    tcp_server::Connection connection;
    connection.send_size(sizeof("hi"));
    connection.write("hi");
}