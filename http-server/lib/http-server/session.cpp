#include "http-server.hpp"

void Session::readRequest(std::shared_ptr<Session> pThis)
{
    asio::async_read_until(
        pThis->socket, 
        pThis->buffer, 
        '\r', 
        [pThis](const error_code& e, std::size_t s)
        {
            std::ostream stream(&pThis->buffer);
            std::string b = pThis->headers.getResponse(stream);
            asio::async_write(
                pThis->socket,
                boost::asio::buffer(b.c_str(), b.length()),
                [](const error_code& e, std::size_t s) {} 
            );
        }
    );
}