//
// Created by Andrew Kireev on 06.11.2020.
//

#ifndef NOSKOOL_FRIENDS_DATA_BASE_H
#define NOSKOOL_FRIENDS_DATA_BASE_H

#include <string>
#include <pqxx/pqxx>
#include <map>
#include <iostream>

class FriendsDataBase {
public:
    // Конектится к базе данных, создается объет таблицы
	explicit FriendsDataBase(std::map<std::string, std::string>& db_settings);

    ~FriendsDataBase();

    int add_friend(int user_1, int user_2);

    std::vector<int> get_all_friends(int user_id);

    int delete_friend(int user_1, int user_2);

    bool is_friend(int user_1, int user_2);

    bool is_opened() const;

private:
    // Table friends_;
    pqxx::connection database_;

	void do_modifying_request(const std::string& sql_request);
	pqxx::result do_select_request(const std::string& sql_request);
};

#endif //NOSKOOL_FRIENDS_DATA_BASE_H
