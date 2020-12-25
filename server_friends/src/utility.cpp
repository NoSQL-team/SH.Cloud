//
// Created by Andrew Kireev on 11.11.2020.
//

#include "utilty.h"

#include <map>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace tcp_network {

	std::map<std::string, std::string> ParseJson::parse(std::string& request) {
		std::map<std::string, std::string> requsts;

		auto iter = request.find('\n');
		requsts.insert({"number", request.substr(0, iter)});
		request.erase(0, iter + 1);
		iter = request.find('\n');
		std::string buffer = request.substr(0, iter);
		buffer = request.substr(13, iter);
		auto bufIter = buffer.find('/');
		buffer = buffer.substr(0, bufIter);
		requsts.insert({"type", buffer});
		request.erase(0, iter + 1);
		iter = request.find('\n');
		requsts.insert({"auth", request.substr(0, iter)});
		request.erase(0, iter + 2);

		if(!request.empty()) {
			std::stringstream ss(request);
			boost::property_tree::ptree pt;
			boost::property_tree::read_json(ss, pt);
			using boost::property_tree::ptree;
			ptree::const_iterator end = pt.end();

			for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
				requsts.insert({std::string(it->first), it->second.get_value<std::string>()});
			}
		}
		return requsts;
	}
}
