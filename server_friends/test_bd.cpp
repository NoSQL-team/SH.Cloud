//
// Created by Andrew Kireev on 04.12.2020.
//


#include "friends_data_base.h"

int main(int argc, char **argv) {

	FriendsDataBase database;

	database.is_opened();

	std::string request = "select * from friends";
	std::cout << database.make_request(request) << std::endl;

	database.add_friend(12, 13);

	auto all_friends = database.get_all_friends(5);
	std::cout << "Список друзей пользователя " + std::to_string(5) << " :" <<std::endl;
	for (auto it : all_friends) {
		std::cout << it << " ";
	}

	return 0;
}
