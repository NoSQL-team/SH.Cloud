//
// Created by lerakrya on 09.12.2020.
//

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_service service;
    tcp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 8082);
    tcp::socket socket(service);
    socket.async_connect(end, [&socket] (const boost::system::error_code& err) {
        std::string requst = "123\napi/users/create/\n4\n\n{\n"
							 "  \"firstname\": \"lera\",\n"
							 "  \"lastname\": \"guseva\",\n"
							 "  \"nickname\": \"lerakrya\",\n"
							 "  \"email\": \"lerakrya8@gmail.com\",\n"
							 "  \"photo\": \"lera.png\",\n"
							 "  \"password\": \"123456\"\n"
							 "}";

        if(!err) {
            boost::asio::write(socket, boost::asio::buffer(requst));
        }
    });
    service.run();

    return 0;
}