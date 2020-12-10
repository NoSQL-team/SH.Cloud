//
// Created by Andrew Kireev on 04.12.2020.
//


#include "friends_data_base.h"

int main(int argc, char **argv) {
	std::map<std::string, std::string> db_settings = {{"dbname", "Friends"}, {"host", "localhost"},
													  {"user", "andrewkireev"}, {"password", ""}};

	FriendsDataBase database(db_settings);

	database.is_opened();
	database.add_friend(12, 13);
	database.add_friend(12, 13);

	auto all_friends = database.get_all_friends(5);
	std::cout << "Список друзей пользователя " + std::to_string(5) << " : ";
	for (auto it : all_friends) {
		std::cout << it << " ";
	}
	std::cout << std::endl;

	database.delete_friend(12, 13);

	database.is_friend(20, 13);



	return 0;
}
