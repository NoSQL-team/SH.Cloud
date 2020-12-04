//
// Created by Andrew Kireev on 11.11.2020.
//


#include "friends_data_base.h"


class const_iterator;

FriendsDataBase::FriendsDataBase() {
	database_ = pqxx::connection("dbname=Friends host=localhost user=andrewkireev password=");
}

FriendsDataBase::~FriendsDataBase() {}

void FriendsDataBase::insert(std::map<std::string, std::string>& request) {}

// Взять данные из таблицы
std::string FriendsDataBase::select(std::map<std::string, std::string>& request) {
    return std::string(" ");
}

std::string FriendsDataBase::make_request(std::string& request) {
	pqxx::nontransaction N(database_);
	pqxx::result r(N.exec(request));

	std::stringstream result;
	for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {
//		std::cout << "ID_1 = " << c[0].as<int>() << std::endl;
		result << "ID_1 = " << c[0].as<int>() << std::endl;
//		std::cout << "ID_2 = " << c[1].as<int>() << std::endl;
		result << "ID_2 = " << c[1].as<int>() << std::endl;
	}
	return result.str();
}

int FriendsDataBase::add_friend(int user_1, int user_2) {
	std::string sql_request("insert into friends values (" + std::to_string(user_1) + ", "
	+ std::to_string(user_2) + ")");
	std::cout << sql_request << std::endl;

	pqxx::work W(database_);
	W.exec(sql_request);
	W.commit();
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

bool FriendsDataBase::is_opened() {
	if (database_.is_open()) {
		std::cout << "Соединение с бд открыто" << std::endl;
		return true;
	}
	std::cout << "Соединение с бд закрыто" << std::endl;
	return false;
}

// Обновить данные в таблице
void FriendsDataBase::update() {}

