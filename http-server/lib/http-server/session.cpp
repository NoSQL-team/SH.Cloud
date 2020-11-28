#include "http-server.hpp"

void Session::handleRequest(std::shared_ptr<Session> pThis, std::string staticPath)
{
    asio::async_read_until(
        pThis->socket, 
        pThis->_buffer, 
        '\r', 
        [pThis, staticPath](const error_code& e, std::size_t s)
        {
            std::istream stream(&pThis->_buffer);
            pThis->_responseBuffer = pThis->headers.getResponse(stream, staticPath);
            // ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
            // responsesHandler->setResponse("");
            async_write(
                pThis->socket,
                boost::asio::buffer(pThis->_responseBuffer.c_str(), pThis->_responseBuffer.length()),
                [pThis](const error_code& e, std::size_t s) {
                    if (!e) {
                        pThis->socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
                    }
                }
            );
        }
    );
}