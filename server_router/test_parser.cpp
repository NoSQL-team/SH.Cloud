//
// Created by Andrew Kireev on 02.12.2020.
//

#include "utilty.h"

int main(int argc, char *argv[]) {
	std::string json = "123423\n"
					   "/api/auth/add/\n"
					   "\n"
					   "{\n"
					   "   \"username\": \"Filechka322\",\n"
					   "   \"password\": \"qwerty\",\n"
					   "   \"id\": 23\n"
					   "}";

	tcp_network::ParseJson parser;
	auto requests = parser.parse(json);
	for (auto it : requests) {
		std::cout << it.first << ": " << it.second << std::endl;
	}

	std::string json_1 = "123423\n"
					   "/api/friends/add/\n"
					   "\n"
					   "{\n"
					   "   \"username\": \"Filechka322\",\n"
					   "   \"password\": \"qwerty\",\n"
					   "   \"id\": 23\n"
					   "}";
//	auto new_json = "5\n" + json;
	tcp_network::print_destination(parser.get_destination(json_1));
	return 0;
}