//
// Created by Andrew Kireev on 10.11.2020.
//

#ifndef TESTS_MOCK_CLASSES_H
#define TESTS_MOCK_CLASSES_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <memory>
#include "utilty.h"
#include "friends_data_base.h"
#include "server_friends.h"

class TestDataBase : public ::testing::Test {
protected:
	void SetUp() {
		database_ = std::make_unique<FriendsDataBase>(db_settings);
	}

	void TearDown() {
		database_.reset();
	}
	std::unique_ptr<FriendsDataBase> database_;
	std::map<std::string, std::string> db_settings = {{"dbname", "Friends"}, {"host", "localhost"},
													  {"user", "andrewkireev"}, {"password", ""}};
};

class MockDatabase : public FriendsDataBase {
public:
	explicit MockDatabase(std::map<std::string, std::string>& db_settings) :
	FriendsDataBase(db_settings) {}

	MOCK_METHOD2(add_friend, bool(int user_1, int user_2));
	MOCK_METHOD1(get_all_friends, std::vector<int>(int user_id));
	MOCK_METHOD2(delete_friend, bool(int user_1, int user_2));
	MOCK_METHOD2(is_friend, bool(int user_1, int user_2));
};

//class TestServer {
//protected:
//	void SetUp() {
//
//	}
//
//	void TearDown() {
//
//	}
//	std::map<std::string, std::string> db_settings = {{"dbname", "Friends"}, {"host", "localhost"},
//													  {"user", "andrewkireev"}, {"password", ""}};
//
//	tcp_network::Server serv;
//};

#endif //TESTS_MOCK_CLASSES_H
