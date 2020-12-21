//
// Created by Andrew Kireev on 06.11.2020.
//

#ifndef NOSKOOL_FRIENDS_DATA_BASE_H
#define NOSKOOL_FRIENDS_DATA_BASE_H

#include <map>
#include <string>
#include <memory>

#include <pqxx/pqxx>



class DataBase {
public:
	explicit DataBase(std::map<std::string, std::string>& db_settings);

	virtual ~DataBase();

	virtual bool is_opened() const;

protected:
	pqxx::connection database_;
};

class FriendsDataBase : public DataBase{
public:
	explicit FriendsDataBase(std::map<std::string, std::string>& db_settings);

	virtual ~FriendsDataBase();

	bool add_friend(int user_1, int user_2);

    std::vector<int> get_all_friends(int user_id);

	bool delete_friend(int user_1, int user_2);

    bool is_friend(int user_1, int user_2);

private:
	void do_modifying_request(std::string& sql_request);
	pqxx::result do_select_request(std::string& sql_request);
};

#endif //NOSKOOL_FRIENDS_DATA_BASE_H
