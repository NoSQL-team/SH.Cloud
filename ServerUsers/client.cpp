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
        std::string requst = "5\n0\ndelete\n{\n"
							 "  \"id\": 15,\n"
							 "  \"firstname\": \"antoha\",\n"
							 "  \"lastname\": \"guseerva\",\n"
							 "  \"nickname\": \"lerafdskrya\",\n"
							 "  \"email\": \"lerakfdsrya8@gmail.com\",\n"
							 "  \"photo\": \"lefdsra.png\"\n"
							 "}";

        if(!err) {
            boost::asio::write(socket, boost::asio::buffer(requst));
        }
    });
    service.run();

    return 0;
}