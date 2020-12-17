//
// Created by Andrew Kireev on 12.11.2020.
//

#include "utilty.h"
#include <map>
#include <string>

namespace tcp_network {

    RequestDestination ParseJson::get_destination(std::string& request) {
		auto iter = request.find('\n');
		request.erase(0, iter + 1);

		iter = request.find('\n');
		std::string destination = request.substr(0, iter);
		destination.erase(0, std::find(destination.begin() + destination.find('/')
									  + 1, destination.end(), '/') - destination.begin() + 1);
		destination.erase(destination.find('/'));

        if (servers_adrs_.count(destination) == 0) {
        	std::cerr << "Несуществующй адрес" << std::endl;
			return RequestDestination::UNKNOWN;
		}
        return servers_adrs_.at(destination);
    }

    std::map<std::string, std::string> ParseJson::parse(std::string& request) {
		std::map<std::string, std::string> requsts;

		auto iter = request.find('\n');
		requsts.insert({"type", request.substr(0, iter)});
		request.erase(0, iter + 1);

		iter = request.find('\n');
		std::string desination = request.substr(0, iter);
		desination.erase(0, std::find(desination.begin() + desination.find('/')
		+ 1, desination.end(), '/') - desination.begin() + 1);
		requsts.insert({"destination", desination.erase(desination.find('/'))});
		request.erase(0, iter + 1);

		std::stringstream ss(request);
		boost::property_tree::ptree pt;
		boost::property_tree::read_json(ss, pt);
		using boost::property_tree::ptree;
		ptree::const_iterator end = pt.end();


		for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
			requsts.insert({std::string(it->first), it->second.get_value<std::string>()});
		}
		return requsts;
    }

	void print_destination(RequestDestination destination) {
		if (destination == RequestDestination::POST_SERV)
		std::cout << "POST_SERV" << std::endl;
		else if (destination == RequestDestination::AUTH_SERV)
		std::cout << "AUTH_SERV" << std::endl;
		else if (destination == RequestDestination::FRIEND_SERV)
		std::cout << "FRIEND_SERV" << std::endl;
		else if (destination == RequestDestination::USER_SERV)
		std::cout << "USER_SERV" << std::endl;
	}

}
