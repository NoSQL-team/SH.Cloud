//
// Created by Andrew Kireev on 10.12.2020.
//

#include "mock_classes.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utilty.h"
#include "friends_data_base.h"

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