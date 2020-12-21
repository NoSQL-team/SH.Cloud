//
// Created by Andrew Kireev on 10.12.2020.
//

#include "mock_classes.h"
#include <gtest/gtest.h>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <string>
#include <chrono>
#include <thread>


using boost::asio::ip::tcp;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

void client(std::string request) {
//	std::cout << request << std::endl;
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"),
						  8081);
	tcp::socket s(io_service);
	s.connect(ep);
	boost::asio::write(s, boost::asio::buffer(request.c_str(), request.size()));
//	io_service.run();
}

void  echo(char** req) {
//	std::cout << "2" << std::endl;
	boost::asio::io_service io_service;
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), 9999));
	socket_ptr sock(new tcp::socket(io_service));
	a.accept(*sock);
	boost::system::error_code error;

//	char req[1024];
	size_t length = sock->read_some(boost::asio::buffer(*req, 1024), error);
	(*req)[length] = '\0';
//	std::cout << length << std::endl;
	io_service.stop();
};

void server_friends() {
//	std::cout << "1" << std::endl;
	std::map<std::string, std::string> db_settings = {{"dbname", "Friends"}, {"host", "localhost"},
													  {"user", "andrewkireev"}, {"password", ""}};

	tcp_network::Server s(8081, db_settings);
}

TEST_F(TestDataBase, insert_in_db) {

	database_->delete_friend(1003, 2003);
	ASSERT_EQ(true, database_->add_friend(1003, 2003));
	ASSERT_EQ(false, database_->add_friend(1003, 2003));
}

TEST_F(TestDataBase, test_is_friend) {

	database_->add_friend(676, 4324);
	ASSERT_TRUE(database_->is_friend(676, 4324));
	database_->delete_friend(14, 132);
	ASSERT_FALSE(database_->is_friend(14, 132));
}

TEST_F(TestDataBase, test_delete) {

	database_->add_friend(777, 494);
	ASSERT_TRUE(database_->is_friend(777, 494));
	ASSERT_TRUE(database_->delete_friend(777, 494));
	ASSERT_FALSE(database_->is_friend(777, 494));
}

TEST(server_bd_interaction, add_friends_1) {

	std::thread tr1(boost::bind(server_friends));
	tr1.detach();

	std::string delete_user = "5\n"
							  "0\n"
							  "delete\n"
							  "\n"
							  "{\n"
							  "  \"user_1\": \"" + std::to_string(432)
							  + "\",\n\"user_2\": \"" + std::to_string(543) + "\"\n}";
	client(delete_user);

	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string request = "5\n"
						  "0\n"
						  "add\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"" + std::to_string(432)
						  + "\",\n\"user_2\": \"" + std::to_string(543) + "\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::thread tr3(boost::bind(client, request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{ \"response\": true }", data_str);

}

TEST(server_bd_interaction, add_friends_already_exist) {

	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string request = "5\n"
						  "0\n"
						  "add\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"" + std::to_string(432)
						  + "\",\n\"user_2\": \"" + std::to_string(543) + "\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::thread tr3(boost::bind(client, request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{ \"response\": false }", data_str);
}

TEST(server_bd_interaction, check_is_friends_true_1) {

	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string request = "5\n"
						  "0\n"
						  "is_friend\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"" + std::to_string(432)
						  + "\",\n\"user_2\": \"" + std::to_string(543) + "\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::thread tr3(boost::bind(client, request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{ \"response\": true }", data_str);
}

TEST(server_bd_interaction, check_is_friends_true_2) {

	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string request = "5\n"
						  "0\n"
						  "is_friend\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"" + std::to_string(543)
						  + "\",\n\"user_2\": \"" + std::to_string(432) + "\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::thread tr3(boost::bind(client, request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{ \"response\": true }", data_str);
}

TEST(server_bd_interaction, check_is_friends_false_1) {


	std::string delete_user = "5\n"
							  "0\n"
							  "delete\n"
							  "\n"
							  "{\n"
							  "  \"user_1\": \"" + std::to_string(12)
							  + "\",\n\"user_2\": \"" + std::to_string(13) + "\"\n}";
	client(delete_user);

	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string request = "5\n"
						  "0\n"
						  "is_friend\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"" + std::to_string(12)
						  + "\",\n\"user_2\": \"" + std::to_string(13) + "\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::thread tr3(boost::bind(client, request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{ \"response\": true }", data_str);
}

TEST(server_bd_interaction, check_is_friends_false_2) {


	std::string delete_user = "5\n"
							  "0\n"
							  "delete\n"
							  "\n"
							  "{\n"
							  "  \"user_1\": \"" + std::to_string(12)
							  + "\",\n\"user_2\": \"" + std::to_string(13) + "\"\n}";
	client(delete_user);

	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string request = "5\n"
						  "0\n"
						  "is_friend\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"" + std::to_string(13)
						  + "\",\n\"user_2\": \"" + std::to_string(12) + "\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::thread tr3(boost::bind(client, request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{ \"response\": true }", data_str);
}


TEST(server_bd_interaction, get_all_friends_1) {
	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string get_all_request = "5\n"
								  "0\n"
								  "get_all\n"
								  "\n"
								  "{\n"
								  "  \"user_1\": \"" + std::to_string(575) +"\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::thread tr3(boost::bind(client, get_all_request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{\n"
			  " \"response\": \"true\",\n"
			  " \"data\": [757, 13, 1654]\n"
			  "}", data_str);
}

TEST(server_bd_interaction, get_all_friends_2) {
	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string get_all_request = "5\n"
								  "0\n"
								  "get_all\n"
								  "\n"
								  "{\n"
								  "  \"user_1\": \"" + std::to_string(555) +"\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::thread tr3(boost::bind(client, get_all_request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{\n"
			  " \"response\": \"true\",\n"
			  " \"data\": [5355, 5335, 1335, 54, 333, 547, 1336]\n"
			  "}", data_str);
}

TEST(server_bd_interaction, get_all_friends_zero_friends) {
	char* data = new char[1024];
	std::thread tr2(boost::bind(echo, &data));
	tr2.detach();
	std::string get_all_request = "5\n"
								  "0\n"
								  "get_all\n"
								  "\n"
								  "{\n"
								  "  \"user_1\": \"" + std::to_string(43423423) +"\"\n}";

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::thread tr3(boost::bind(client, get_all_request));
	tr3.detach();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::string data_str = std::string(data);
	delete []data;
	ASSERT_EQ("{\n"
			  " \"response\": \"true\",\n"
			  " \"data\": []\n"
			  "}", data_str);
}




int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}