//
// Created by lerakry on 10.12.2020.
//
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "UsersDatabase.h"
#include "HandlerUser.h"

#include <iostream>

using boost::property_tree::ptree;
using std::string;


std::map<string, string> parser_json(std::stringstream& request) {
	ptree pt;
	if (!request.str().empty()) {
		boost::property_tree::read_json(request, pt);
		std::map<string, string> result;
		ptree::const_iterator end = pt.end();
		char alf = 'A';
		for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
			result[alf + std::string(it->first)] = it->second.get_value<string>();
			alf++;
		}
		return result;
	}
	return {};
}

int main() {

	string example = "{\n"
					 "  \"id\": 5,\n"
					 "  \"firstname\": \"lera\",\n"
					 "  \"lastname\": \"guseva\",\n"
					 "  \"nickname\": \"lerakrya\",\n"
					 "  \"email\": \"lerakrya8@gmail.com\",\n"
					 "  \"photo\": \"lera.png\"\n"
					 "}";

	auto db = UsersDatabase();
	std::stringstream stream(example);


	auto m = parser_json(stream);


	return 0;
}