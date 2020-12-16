////
//// Created by Andrew Kireev on 08.11.2020.
////
//
//TEST(MockServerRouter, test_redirecton) {
//    uint16_t port = 1234;
//    std::string ip = "127.0.0.1";
//
//    MockServerRouter server(ip, port);
//
//    tcp_network::Connection con(ip, port);
//
//    std::string request = "123423\n"
//                          "0\n"
//                          "get/\n"
//                          "\n"
//                          "{"
//                          "   \"id\": \"4342332\",\n"
//                          "}";
//
//    con.write(request);
//
//    EXPECT_CALL(server, handle_client(testing::_,
//                                    testing::_)).Times(testing::AtLeast(1));
//
//}
//
//TEST(MockServerRouter, test_accept_client) {
//    uint16_t port = 1234;
//    std::string ip = "127.0.0.1";
//
//    MockServerRouter server(ip, port);
//
//    tcp_network::Connection con(ip, port);
//
//    std::string request = "123423\n"
//                          "0\n"
//                          "get/\n"
//                          "\n"
//                          "{"
//                          "   \"id\": \"4342332\",\n"
//                          "}";
//
//    con.write(request);
//
//    EXPECT_CALL(server, accept_clients()).Times(testing::AtLeast(1));
//}
//
//TEST(MockServerRouter, test_redirecting_to_friends) {
//    uint16_t port = 1234;
//    std::string ip = "127.0.0.1";
//
//    MockServerRouter server(ip, port);
//
//    tcp_network::Connection con(ip, port);
//
//    std::string request = "123423\n";
//
//    con.write(request);
//
//    EXPECT_CALL(server, build_rout(testing::_)).Times(testing::AtLeast(1));
//}
//
//TEST(MockServerRouter, test_redirecting_to_user) {
//    uint16_t port = 1234;
//    std::string ip = "127.0.0.1";
//
//    MockServerRouter server(ip, port);
//
//    std::string request = "123423\n";
//    EXPECT_EQ(tcp_network::RequestDestination::FRIEND_SERV, server.build_rout(request));
//}
//
//TEST(MockServerRouter, test_redirecting_to_friends_2) {
//    uint16_t port = 1234;
//    std::string ip = "127.0.0.1";
//
//    MockServerRouter server(ip, port);
//
//    std::string request = "42332\n";
//    EXPECT_EQ(tcp_network::RequestDestination::USER_SERV, server.build_rout(request));
//}
//
//
int main(int argc, char **argv) {
}
