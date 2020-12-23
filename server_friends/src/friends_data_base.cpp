//
// Created by Andrew Kireev on 11.11.2020.
//

#include "../include/friends_data_base.h"

#include <pqxx/pqxx>

#include <iostream>
#include <thread>
#include <chrono>

DataBase::DataBase(std::map<std::string, std::string> &db_settings)  {
	str_db_settings = ("dbname=" + db_settings["dbname"] +
							  " host=" + db_settings["host"] +" user=" + db_settings["user"] +
							  " password=" + db_settings["password"] + " port=27002");
	try {
		database_ = std::make_unique<pqxx::connection>(str_db_settings);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Connecting!" << std::endl;
}

FriendsDataBase::FriendsDataBase(std::map<std::string, std::string>& db_settings) : DataBase(db_settings){ }

DataBase::~DataBase() {}

FriendsDataBase::~FriendsDataBase() {}

bool FriendsDataBase::add_friend(int user_1, int user_2) {

	if (is_friend(user_1, user_2)) {
		std::cout << std::to_string(user_1) + " и "
		+ std::to_string(user_2) + " уже друзья" << std::endl;
		return false;
	}

	std::cout << "/* message */" << std::endl;

	auto form_sql_request = [](int user_id_1, int user_id_2){
		return "insert into friends values (" + std::to_string(user_id_1) + ", "
			   + std::to_string(user_id_2) + ")";
	};

	std::cout << "/* message */" << std::endl;

	std::string sql_request = form_sql_request(user_1, user_2);
	std::cout << sql_request << std::endl;
	do_modifying_request(sql_request);
	std::string sql_request_2 = form_sql_request(user_2, user_1);
	std::cout << sql_request_2 << std::endl;
	do_modifying_request(sql_request_2);

	return true;
}

std::vector<int> FriendsDataBase::get_all_friends(int user_id) {
	std::string sql_request("select second_id from friends where first_id = " + std::to_string(user_id));
	std::cout << sql_request << std::endl;

	pqxx::result r = do_select_request(sql_request);

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



	pqxx::result r = do_select_request(sql_request);

	std::cout << "/* message */" << std::endl;

	pqxx::result::const_iterator c = r.begin();
	bool is_friend = c[0].as<int>();
	if (is_friend) {
		std::cout << std::to_string(user_1)
		+ " и " + std::to_string(user_2) + " друзья" << std::endl;
		return true;
	}
	std::cout << std::to_string(user_1)
				 + " и " + std::to_string(user_2) + " не друзья" << std::endl;
	return false;
}

bool FriendsDataBase::delete_friend(int user_1, int user_2) {

	auto form_sql_request = [](int user_id_1, int user_id_2) {
		return "delete from friends where first_id = " +
			   std::to_string(user_id_1) + " and second_id = " + std::to_string(user_id_2);
	};


	std::string sql_request_1 = form_sql_request(user_1, user_2);
	std::cout << sql_request_1 << std::endl;
	do_modifying_request(sql_request_1);

	std::string sql_request_2 = form_sql_request(user_2, user_1);
	std::cout << sql_request_2 << std::endl;
	do_modifying_request(sql_request_2);

	return true;
}

bool DataBase::is_opened() const {
	if (database_->is_open()) {
		std::cout << "Соединение с бд открыто" << std::endl;
		return true;
	}
	std::cout << "Соединение с бд закрыто" << std::endl;
	return false;
}


void FriendsDataBase::do_modifying_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work W(con);
	W.exec(sql_request);
	W.commit();
}

pqxx::result FriendsDataBase::do_select_request(std::string& sql_request) {
	pqxx::connection con(str_db_settings);
	pqxx::work N(con);
	pqxx::result R = N.exec(sql_request);
	N.commit();
	return R;
}


