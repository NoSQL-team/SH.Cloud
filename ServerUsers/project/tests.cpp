//
// Created by Andrew Kireev on 23.12.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HandlerUser.h"
#include "UsersDatabase.h"

#include <chrono>
#include <thread>

#include <boost/bind.hpp>

class MockDataBase : public UsersDatabase {
public:
	MOCK_METHOD2(insert, bool(const std::map<std::string, std::string>& users_data, int id_user));
	MOCK_METHOD0(all_users, std::string());
	MOCK_METHOD1(data_user, std::string(int id));
	MOCK_METHOD1(exist, bool(int id));
	MOCK_METHOD1(id_by_nick, std::string(std::string& nickname));
	MOCK_METHOD2(update, bool(const std::map<std::string, std::string>& data, int id_user));
};


void start_session(boost::asio::io_service& ioService, MockDataBase& db) {
	Session session(ioService, db);
	session.start();
}


TEST(handler_work_with_bd, update) {
	MockDataBase db;
	boost::asio::io_service ioService;
	Session session(ioService, db);
	HandlerUser handler(ioService, session, db);

	std::string example = "123\napi/users/update/\n34\n\n{\n"
					  "  \"id\": 34,\n"
					  "  \"lastname\": \"guseva\",\n"
					  "  \"nickname\": \"lerakrya\"\n"
					  "}";

	EXPECT_CALL(db, update(testing::_,
						  testing::_));

	handler.handle_request(example);
}

TEST(handler_work_with_bd, data_user) {
	MockDataBase db;
	boost::asio::io_service ioService;
	Session session(ioService, db);
	HandlerUser handler(ioService, session, db);

	std::string example = "123\napi/users/5/\n4\n\n";

	EXPECT_CALL(db, data_user(testing::_)).Times(2);

	handler.handle_request(example);
}

TEST(handler_work_with_bd, get_all_users) {
	MockDataBase db;
	boost::asio::io_service ioService;
	Session session(ioService, db);
	HandlerUser handler(ioService, session, db);

	std::string example = "123\napi/users/all/\n4\n\n";

	EXPECT_CALL(db, all_users()).Times(testing::AtLeast(1));

	handler.handle_request(example);
}

TEST(handler_work_with_bd, id_by_nick) {
	MockDataBase db;
	boost::asio::io_service ioService;
	Session session(ioService, db);
	HandlerUser handler(ioService, session, db);

	std::string example = "123\napi/users/lerakrya/\n4\n\n";

	EXPECT_CALL(db, id_by_nick(testing::_)).Times(1);

	handler.handle_request(example);
}

TEST(handler_work_with_bd, exist) {
	MockDataBase db;
	boost::asio::io_service ioService;
	Session session(ioService, db);
	HandlerUser handler(ioService, session, db);

	std::string example = "123\napi/users/exists/5/\n4\n\n";

	EXPECT_CALL(db, exist(testing::_)).Times(1);

	handler.handle_request(example);
}

TEST(test_database, test_insert) {
	UsersDatabase database;
	std::map<std::string, std::string> request = {{"Bfirstname", "lera"},
												  {"Clastname", "guseva"},
												  {"Dnickname", "lerakrya"},
												  {"Eemail", "lerakrya8@gmail.com"},
												  {"Fphoto", "lera.png"}};

	EXPECT_TRUE(database.insert(request, -1));
	EXPECT_FALSE(database.insert(request, 5));
}

TEST(test_database, test_update) {
	UsersDatabase database;
	std::map<std::string, std::string> request = {{"Aid", "34"},
											   	  {"Bfirstname", "valeriya"},
												  {"Dnickname", "lerakrya8"}};

	EXPECT_TRUE(database.update(request, 34));
	EXPECT_FALSE(database.update(request, 3));
}

TEST(test_database, test_data_user) {
	UsersDatabase database;

	EXPECT_EQ(database.data_user(34), "{\n"
								  	"  \"firstname\": \"valeriya\",\n"
								  	"  \"lastname\": \"guseva\",\n"
								  	"  \"nickname\": \"lerakrya8\",\n"
		  							"  \"email\": \"lerakrya8@gmail.com\",\n"
									"  \"photo\": \"lera.png\"\n"
		 "}");
	EXPECT_EQ(database.data_user(5), "No user");
}

TEST(test_database, test_get_id_by_nic) {
	UsersDatabase database;

	std::string nickname = "lerakrya8";

	EXPECT_EQ(database.id_by_nick(nickname), "{\n  \"id\": 34\n}");
}

TEST(test_database, test_exist) {
	UsersDatabase database;

	EXPECT_TRUE(database.exist(34));
	EXPECT_FALSE(database.exist(5));
}

TEST(test_parser, test_create_request) {
	boost::asio::io_service io_service;
	UsersDatabase data_base_;
	Session session_(io_service, data_base_);
	HandlerUser handler(io_service, session_, data_base_);

	std::string request = "123\napi/users/create/\n4\n\n{\n"
						  "  \"firstname\": \"lera\",\n"
						  "  \"lastname\": \"guseva\",\n"
						  "  \"nickname\": \"lerakrya\",\n"
						  "  \"email\": \"lerakrya8@gmail.com\",\n"
						  "  \"photo\": \"lera.png\"\n"
						  "}";

	int num_request, id_user, id_exists, data_id;
	auto [method, parse_json] = handler.parse_request(request, num_request, id_user, id_exists, data_id);
	EXPECT_EQ(method, "create");
	std::map<std::string, std::string> exp = {{"Bfirstname", "lera"},
				{"Clastname", "guseva"},
				{"Dnickname", "lerakrya"},
				{"Eemail", "lerakrya8@gmail.com"},
				{"Fphoto", "lera.png"}};
	EXPECT_EQ(parse_json, exp);
}

TEST(test_parser, test_update_request) {
	boost::asio::io_service io_service;
	UsersDatabase data_base_;
	Session session_(io_service, data_base_);
	HandlerUser handler(io_service, session_, data_base_);

	std::string request = "123\napi/users/update/\n4\n\n{\n"
						  "  \"id\": 5,\n"
						  "  \"lastname\": \"guseva\",\n"
						  "  \"nickname\": \"lerakrya8\"\n"
						  "}";

	int num_request, id_user, id_exists, data_id;
	auto [method, parse_json] = handler.parse_request(request, num_request, id_user, id_exists, data_id);
	EXPECT_EQ(method, "update");
	std::map<std::string, std::string> exp = {{"Aid", "5"},
											  {"Clastname", "guseva"},
											  {"Dnickname", "lerakrya8"}};
	EXPECT_EQ(parse_json, exp);
}

TEST(test_parser, test_exist_request) {
	boost::asio::io_service io_service;
	UsersDatabase data_base_;
	Session session_(io_service, data_base_);
	HandlerUser handler(io_service, session_, data_base_);

	std::string request = "123\napi/users/exists/5/\n4\n\n";

	int num_request, id_user, id_exists, data_id;
	auto [method, parse_json] = handler.parse_request(request, num_request, id_user, id_exists, data_id);
	EXPECT_EQ(method, "exists");
	EXPECT_EQ(id_exists, 5);
}

TEST(test_parser, test_data_request) {
	boost::asio::io_service io_service;
	UsersDatabase data_base_;
	Session session_(io_service, data_base_);
	HandlerUser handler(io_service, session_, data_base_);

	std::string request = "123\napi/users/5/\n4\n\n";

	int num_request, id_user, id_exists, data_id;
	auto [method, parse_json] = handler.parse_request(request, num_request, id_user, id_exists, data_id);
	EXPECT_EQ(method, "5");
}

TEST(test_parser, test_nickname_request) {
	boost::asio::io_service io_service;
	UsersDatabase data_base_;
	Session session_(io_service, data_base_);
	HandlerUser handler(io_service, session_, data_base_);

	std::string request = "123\napi/users/lerakrya/\n4\n\n";

	int num_request, id_user, id_exists, data_id;
	auto [method, parse_json] = handler.parse_request(request, num_request, id_user, id_exists, data_id);
	EXPECT_EQ(method, "lerakrya");
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}