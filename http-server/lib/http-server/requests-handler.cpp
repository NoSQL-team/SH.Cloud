#include "http-server.hpp"

void RequestsHandler::parseFirstHeader(std::string line)
{
    std::stringstream ssRequestLine(line);
    ssRequestLine >> method;
    ssRequestLine >> url;
    ssRequestLine >> version;
}

void RequestsHandler::parseNextHeaders(std::string line)
{       
    std::stringstream ssHeader(line);
    std::string headerName;
    std::getline(ssHeader, headerName, ':');
    
    std::string value;
    std::getline(ssHeader, value);
    headers[headerName] = value;
}

void RequestsHandler::parseHeaders(std::ostream& stream) {

}

void RequestsHandler::responseFormation(std::string status, std::string body = "") {

}

std::string RequestsHandler::getResponse(std::ostream& stream)
{
    parseHeaders(stream);

    if (true) {
        // кидаем запрос если запрос это запрос к api
        connection;

        ResponsesHandler* responsesHandler = ResponsesHandler::getInstance();
        
        // получаем из responseHandlr + заголовки и отвечаем
    } else {
        // отдаём статику
    }

    std::string sHTML = "<html></html>\n";
    std::stringstream ssOut;
    ssOut << "HTTP/1.1 200 OK\n" << "content-type: text/html\n" << "content-length: " << sHTML.length() << std::endl << std::endl << sHTML;

    return ssOut.str();
}
