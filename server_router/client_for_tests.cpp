//
// Created by Andrew Kireev on 04.12.2020.
//

#include <boost/asio.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;


int main(int argc, char **argv) {

	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini("../router_settings.ini", pt);
	io_service service;
	ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"),
						  pt.get<int>("router.port"));
	ip::tcp::socket sock(service);
	sock.async_connect(ep, [&sock](const system::error_code& error) {
		if (!error) {
			std::string requst = "123423\n"
								 "/api/friends/add/\n"
								 "4\n"
								 "\n"
								 "{\n"
								 "   \"username\": \"Filechka322\",\n"
								 "   \"password\": \"qwerty\",\n"
								 "   \"id\": 23\n"
								 "}";

			boost::asio::write(sock, boost::asio::buffer(requst.c_str(), requst.size()));
		}
	});
	service.run();

	return 0;
}
