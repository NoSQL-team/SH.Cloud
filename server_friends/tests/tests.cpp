//
// Created by Andrew Kireev on 08.11.2020.
//


#include "mock_classes.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utilty.h"
#include "friends_data_base.h"

// Тест парсера Json

TEST(Test_parser, parse_test_1) {
    tcp_network::ParseJson parser;

    std::string request = "5\n"
						  "0\n"
						  "add\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"333\",\n"
						  "  \"user_2\": \"444\"\n"
						  "}";

    std::map<std::string, std::string> expected = {{"destination", "5"},
												   {"priority", "0"},
												   {"type", "add"},
												   {"user_1", "333"},
												   {"user_2", "444"}};

    ASSERT_EQ(expected, parser.parse(request));
}

TEST(Test_parser, parse_test_2) {
	tcp_network::ParseJson parser;

	std::string request = "5\n"
						  "0\n"
						  "add\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"333\",\n"
						  "  \"user_2\": \"444\"\n"
						  "}";

	std::map<std::string, std::string> expected = {{"destination", "5"},
												   {"priority", "4"},
												   {"type", "add"},
												   {"user_4", "353"},
												   {"user_2", "444"}};

	bool result = false;
	if (expected == parser.parse(request))
		result = true;

	ASSERT_FALSE(result);
}

TEST(Test_parser, test_get_destination) {
	tcp_network::ParseJson parser;

	std::string request_1 = "1\n"
						  "0\n"
						  "add\n"
						  "\n"
						  "{\n"
						  "  \"user_1\": \"333\",\n"
						  "}";

	std::string request_2 = "2\n"
							"0\n"
							"add\n"
							"\n"
							"{\n"
							"  \"user_1\": \"333\",\n"
							"}";

	std::string request_3 = "3\n"
							"0\n"
							"add\n"
							"\n"
							"{\n"
							"  \"user_1\": \"333\",\n"
							"}";


	ASSERT_EQ(tcp_network::RequestDestination::AUTH_SERV,
		   parser.get_destination(request_1));
	ASSERT_EQ(tcp_network::RequestDestination::USER_SERV,
			  parser.get_destination(request_2));
	ASSERT_EQ(tcp_network::RequestDestination::HTTP_SERV,
			  parser.get_destination(request_3));
}

TEST_F(TestDataBase, insert_in_db) {

	database_->delete_friend(1003, 2003);
	ASSERT_EQ(200, database_->add_friend(1003, 2003));
	ASSERT_EQ(0, database_->add_friend(1003, 2003));
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




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}