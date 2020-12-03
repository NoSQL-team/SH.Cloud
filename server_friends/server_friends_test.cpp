//
// Created by Andrew Kireev on 03.12.2020.
//

#include "server_friends.h"

using namespace boost;
using namespace boost::system;
using namespace boost::asio;


int main(int argc, char *argv[]) {
	try {
		tcp_network::Server s(8081);

	}
	catch (std::exception &e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}