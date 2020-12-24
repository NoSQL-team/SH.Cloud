//
// Created by Andrew Kireev on 11.11.2020.
//

#include "../include/friends_data_base.h"

#include <pqxx/pqxx>

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <tuple>

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

	auto form_sql_request = [](int user_id_1, int user_id_2){
		return "insert into friends values (" + std::to_string(user_id_1) + ", "
			   + std::to_string(user_id_2) + ")";
	};

	std::string sql_request = form_sql_request(user_1, user_2);
	std::cout << sql_request << std::endl;
	do_modifying_request(sql_request);

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
	result.push_back(user_id);
	return result;
}


// return value = 1 первый подписан на второго
// return value = 2 второй подписан на первого
// return value = 3 друзья

int FriendsDataBase::is_friend(int user_1, int user_2) {
	int result = 0;
	std::string sql_request("select count(*) from friends where first_id = "
	+ std::to_string(user_1) + " and second_id = " + std::to_string(user_2));
	std::cout << sql_request << std::endl;

	pqxx::result r = do_select_request(sql_request);

	pqxx::result::const_iterator c = r.begin();
	bool is_friend_1 = c[0].as<int>();
	std::cout << "первый друг второго" << is_friend_1 << std::endl;
	if (is_friend_1)
		result = 1;

	std::string sql_request_2("select count(*) from friends where first_id = "
							+ std::to_string(user_2) + " and second_id = " + std::to_string(user_1));
	std::cout << sql_request_2 << std::endl;


	pqxx::result r2 = do_select_request(sql_request_2);

	is_friend_1 = false;
	pqxx::result::const_iterator c2 = r2.begin();
	is_friend_1 = c2[0].as<int>();

	std::cout << "второй друг перовго" << is_friend_1 << std::endl;

	if (is_friend_1)
		result += 2;

	return result;
}

bool FriendsDataBase::delete_friend(int user_1, int user_2) {

	auto form_sql_request = [](int user_id_1, int user_id_2) {
		return "delete from friends where first_id = " +
			   std::to_string(user_id_1) + " and second_id = " + std::to_string(user_id_2);
	};


	std::string sql_request_1 = form_sql_request(user_1, user_2);
	std::cout << sql_request_1 << std::endl;
	do_modifying_request(sql_request_1);
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

std::tuple<int, int, int> FriendsDataBase::get_statistic(int user_1) {
	std::string sql_requst_1 = "select distinct second_id "
						  "from friends where first_id = " + std::to_string(user_1);

	std::cout << sql_requst_1 << std::endl;

	pqxx::result result = do_select_request(sql_requst_1);
	std::vector<int> user_1_to_user_2;
	for (pqxx::result::const_iterator c = result.begin(); c != result.end(); ++c) {
		user_1_to_user_2.push_back(c[0].as<int>());
	}

	std::cout << user_1_to_user_2.size() << std::endl;

	std::string sql_requst_2 = "select distinct first_id "
							   "from friends where second_id = " + std::to_string(user_1);

	std::cout << sql_requst_2 << std::endl;

	pqxx::result result_2 = do_select_request(sql_requst_2);
	std::vector<int> user_2_to_user_1;
	for (pqxx::result::const_iterator c = result_2.begin(); c != result_2.end(); ++c) {
		user_2_to_user_1.push_back(c[0].as<int>());
	}
	std::cout << user_2_to_user_1.size() << std::endl;

	int friendship_amount = 0;
	std::vector<int> el_to_del;
	for (int id : user_1_to_user_2) {
		if (std::find(user_2_to_user_1.begin(), user_2_to_user_1.end(), id)
		!= user_2_to_user_1.end()) {
			++friendship_amount;
			el_to_del.push_back(id);
		}
	}
	std::cout << "Число друзей1 " << friendship_amount << std::endl;

	user_1_to_user_2.erase(std::remove_if(user_1_to_user_2.begin(),
									   user_1_to_user_2.end(), [&el_to_del](int elem){
		if (std::find(el_to_del.begin(), el_to_del.end(), elem) != el_to_del.end()) {
			std::cout << "удаляем " << elem << std::endl;
			return true;
		}
		return false;
	}), user_1_to_user_2.end());

	user_2_to_user_1.erase(std::remove_if(user_2_to_user_1.begin(),
										  user_2_to_user_1.end(), [&el_to_del](int elem){
			if (std::find(el_to_del.begin(), el_to_del.end(), elem) != el_to_del.end()) {
				std::cout << "удаляем " << elem << std::endl;
				return true;
			}
			return false;
	}), user_2_to_user_1.end());


	std::cout << "Число друзей " << friendship_amount << std::endl;

	return std::make_tuple(user_1_to_user_2.size(), user_2_to_user_1.size(), friendship_amount);
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


