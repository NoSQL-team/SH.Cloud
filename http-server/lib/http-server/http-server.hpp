#ifndef HTTTP_SERVER_NOSOOL
#define HTTP_SERVER_NOSKOOL

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <iostream>
#include <vector>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;
using namespace std::placeholders;

class Connection
{
    int sock;
    struct sockaddr_in addr;

    void connect();
    void close();

public:
    Connection() {};
    std::string getResponse(std::string request);
};

class RequestsHandler
{
    std::string method;
    std::string url;
    std::string version;
    std::string body;
    std::map<std::string, std::string> headers;
    Connection connection;

    void parseFirstHeader(std::string line);
    void parseNextHeaders(std::string line);
    void parseHeaders(std::ostream& stream);
    void responseFormation(std::string status, std::string body);

public:
    std::string getResponse(std::ostream& stream);
};

class Session
{
    asio::streambuf buffer;
    RequestsHandler headers;

    static void readRequest(std::shared_ptr<Session> pThis);
    
public:
    ip::tcp::socket socket;

    Session(io_service& io_service)
        :socket(io_service)
    {}
    
    static void handleRequest(std::shared_ptr<Session> pThis)
    {
        readRequest(pThis);
    }
};

#endif // !HTTTP_SERVER_NOSOOL