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
		database_ = std::make_unique<FriendsDataBase>();
	}

	void TearDown() {
		database_.reset();
	}
	std::unique_ptr<FriendsDataBase> database_;
};
#endif //TESTS_MOCK_CLASSES_H
