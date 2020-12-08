//
// Created by Andrew Kireev on 04.12.2020.
//

#include <boost/asio.hpp>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;


int main(int argc, char **argv) {

	io_service service;
	ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"),
						  8081);
	ip::tcp::socket sock(service);
	sock.async_connect(ep, [&sock](const system::error_code& error) {
		if (!error) {
			std::string requst = "4\n"
								 "0\n"
								 "create/\n"
								 "\n"
								 "{\n"
								 "   \"username\": \"Filechka322\",\n"
								 "   \"email\": \"UUU@gmail.com\",\n"
								 "   \"password\": \"qwerty\"\n"
								 "}";

//					std::istream(&data_) >> requst;
			boost::asio::write(sock, boost::asio::buffer(requst.c_str(), requst.size()));

//			std::cout << data_ << std::endl;
		}
	});
	service.run();

	return 0;
}
