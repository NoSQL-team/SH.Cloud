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

class ConnectionSend
{
    int sock;
    struct sockaddr_in addr;

    int connect();
    int close();

public:
    ConnectionSend() {};
    int sendRequest(std::string request);
};

class RequestsHandler
{
    std::string method;
    std::string url;
    std::string version;
    std::string body;
    std::map<std::string, std::string> headers;
    ConnectionSend connection;

    void parseFirstHeader(std::string line);
    void parseNextHeaders(std::string line);
    void parseHeaders(std::ostream& stream);
    void responseFormation(std::string status, std::string body);

public:
    RequestsHandler() {};
    std::string getResponse(std::ostream& stream);
};

class Session
{
    asio::streambuf buffer;
    RequestsHandler headers;
    
public:
    ip::tcp::socket socket;

    Session(io_service& io_service)
        :socket(io_service)
    {}
    
    static void handleRequest(std::shared_ptr<Session> pThis);
};

class ResponsesHandler
{
protected:
    ResponsesHandler() {}

    static ResponsesHandler* _objPtr;
    std::vector<std::map<size_t, std::string>> _responses;
    static std::mutex _mutex;

public:
    ResponsesHandler(ResponsesHandler &other) = delete;
    void operator=(const ResponsesHandler &) = delete;
    static ResponsesHandler* getInstance();
    std::string getResponse(size_t number);
    void setResponse(std::string response);
};

#endif // !HTTTP_SERVER_NOSOOL