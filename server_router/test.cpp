//
// Created by Andrew Kireev on 30.11.2020.
//

//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <memory>
#include "server_router.h"


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