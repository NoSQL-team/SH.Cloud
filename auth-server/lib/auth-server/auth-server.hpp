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
#include <pqxx/pqxx>

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

    void parseHeaders(std::ostream& line);
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

class DateBaseConnection
{
protected:
    DateBaseConnection() {}

    static DateBaseConnection* _objPtr;
    static std::mutex _mutex;
    pqxx::connection _db;

public:
    DateBaseConnection(DateBaseConnection &other) = delete;
    void operator=(const DateBaseConnection &) = delete;
    static DateBaseConnection* getInstance();
    std::string getResponse(size_t number);
    void setResponse(std::string response);
};

class AuthServer
{
private:
    
public:
    void acceptAndRun(ip::tcp::acceptor& acceptor, io_service& io_service);
    void run(uint16_t port);
    AuthServer() {};
    ~AuthServer() {};
};

#endif // !HTTTP_SERVER_NOSOOL