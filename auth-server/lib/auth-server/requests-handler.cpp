#include "auth-server.hpp"

void RequestsHandler::parseHeaders(std::ostream& line)
{

}

void RequestsHandler::responseFormation(std::string status, std::string body = "") {

}

std::string RequestsHandler::getResponse(std::ostream& stream)
{
    parseHeaders(stream);

    // кидаем запрос если запрос это запрос к api
    connection;

    // DateBaseConnection* dateBase = DateBaseConnection::getInstance();

    // получаем из dateBase + заголовки и отвечаем

    std::stringstream ssOut;
    ssOut << "12\n" << "\n" << "{\"token\": \"123ewfewsags.esfsef.sefsefsefsef\"}";

    return ssOut.str();
}
