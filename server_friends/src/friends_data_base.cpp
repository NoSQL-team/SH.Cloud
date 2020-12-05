//
// Created by Andrew Kireev on 11.11.2020.
//

#include <algorithm>
#include "friends_data_base.h"



FriendsDataBase::FriendsDataBase() {
	database_ = pqxx::connection("dbname=Friends host=localhost user=andrewkireev password=");
}

FriendsDataBase::~FriendsDataBase() {
	database_.close();
}


int FriendsDataBase::add_friend(int user_1, int user_2) {
	std::vector<int> all_friends_user1 = get_all_friends(user_1);

	if (is_friend(user_1, user_2)) {
		std::cout << std::to_string(user_1) + " и "
		+ std::to_string(user_2) + " уже друзья" << std::endl;
		return 0;
	}
	std::string sql_request("insert into friends values (" + std::to_string(user_1) + ", "
	+ std::to_string(user_2) + ")");
	std::cout << sql_request << std::endl;

	pqxx::work W(database_);
	W.exec(sql_request);
	W.commit();

	std::string sql_request_2("insert into friends values (" + std::to_string(user_2) + ", "
							+ std::to_string(user_1) + ")");
	std::cout << sql_request_2 << std::endl;

	pqxx::work W2(database_);
	W2.exec(sql_request_2);
	W2.commit();
	return 200;
}

std::vector<int> FriendsDataBase::get_all_friends(int user_id) {
	std::string sql_request("select second_id from friends where first_id = " + std::to_string(user_id));
	std::cout << sql_request << std::endl;

	pqxx::nontransaction N(database_);
	pqxx::result r(N.exec(sql_request));

	std::vector<int> result;
	for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {
		result.push_back(c[0].as<int>());
	}
	return result;
}

bool FriendsDataBase::is_friend(int user_1, int user_2) {
	std::string sql_request("select count(*) from friends where first_id = "
	+ std::to_string(user_1) + " and second_id = " + std::to_string(user_2));
	std::cout << sql_request << std::endl;

	pqxx::nontransaction N(database_);
	pqxx::result r(N.exec(sql_request));
	pqxx::result::const_iterator c = r.begin();
	bool is_friend = c[0].as<bool>();
	if (is_friend) {
		std::cout << std::to_string(user_1)
		+ " и " + std::to_string(user_2) + " друзья" << std::endl;
		return true;
	}
	std::cout << std::to_string(user_1)
				 + " и " + std::to_string(user_2) + " не друзья" << std::endl;
	return false;
}

int FriendsDataBase::delete_friend(int user_1, int user_2) {
	std::string sql_request_1("delete from friends where first_id = " +
	std::to_string(user_1) + " and second_id = " + std::to_string(user_2));
	std::cout << sql_request_1 << std::endl;

	pqxx::work W(database_);
	W.exec(sql_request_1);
	W.commit();

	std::string sql_request_2("delete from friends where first_id = " +
							  std::to_string(user_2) + " and second_id = " + std::to_string(user_1));
	std::cout << sql_request_2 << std::endl;
	pqxx::work W2(database_);
	W2.exec(sql_request_2);
	W2.commit();
	return 1;
}

bool FriendsDataBase::is_opened() {
	if (database_.is_open()) {
		std::cout << "Соединение с бд открыто" << std::endl;
		return true;
	}
	std::cout << "Соединение с бд закрыто" << std::endl;
	return false;
}


