//
// Created by Andrew Kireev on 02.12.2020.
//

#include "utilty.h"

int main(int argc, char *argv[]) {
	std::string json = "{ \"squadName\": \"Super hero squad\", \"homeTown\": \"Metro City\","
					"\"formed\": 2016, \"secretBase\": \"Super tower\", \"active\": true }";

	tcp_network::ParseJson parser;
	std::stringstream ss(json);

	boost::property_tree::ptree pt;
	boost::property_tree::read_json(ss, pt);
	auto requests = parser.print(pt);
	for (auto it : requests) {
		std::cout << it.first << ": " << it.second << std::endl;
	}
	return 0;
}