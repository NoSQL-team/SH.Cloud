//
// Created by Andrew Kireev on 02.12.2020.
//

#include "utilty.h"

int main(int argc, char *argv[]) {
	std::string json = "5\n"
					   "0\n"
					   "create/\n"
					   "\n"
					   "{\n"
					   "   \"username\": \"Filechka322\",\n"
					   "   \"email\": \"UUU@gmail.com\",\n"
					   "   \"password\": \"qwerty\"\n"
					   "}";

	tcp_network::ParseJson parser;
	auto requests = parser.parse(json);
	for (auto it : requests) {
		std::cout << it.first << ": " << it.second << std::endl;
	}

	auto new_json = "5\n" + json;
	tcp_network::print_destination(parser.get_destination(new_json));
	return 0;
}