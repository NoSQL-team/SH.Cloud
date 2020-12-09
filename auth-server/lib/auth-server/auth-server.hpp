#ifndef AUTH_SERVER_NOSOOL
#define AUTH_SERVER_NOSOOL

#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <pqxx/pqxx>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

class RequestsHandler
{
public:
    RequestsHandler() {};
    std::string getResponse(std::istream& stream);
};

class Session:  public std::enable_shared_from_this<Session>
{
public:
    Session(ip::tcp::socket socket)
        : _socket(std::move(socket))
        ,_strand(_socket.get_io_service()) {}

    void start();
private:
    ip::tcp::socket _socket;
    asio::streambuf _buffer;
    std::string _responseBuffer;
    RequestsHandler headers;
    boost::asio::io_service::strand _strand;
};

class DateBaseConnection
{
protected:
    DateBaseConnection(
        std::string dbname,
        std::string host,
        std::string user,
        std::string password
    ) {
        std::stringstream ss;
        ss << "dbname=" << dbname << " host=" << host << " user=" << user << " password=" << password;
        _db = new pqxx::connection(ss.str());
    }
    ~DateBaseConnection() {
        delete _db;
    }

    static DateBaseConnection* _objPtr;
    static std::mutex _mutex;

public:
    DateBaseConnection(DateBaseConnection &other) = delete;
    void operator=(const DateBaseConnection &) = delete;
    static DateBaseConnection* getInstance();
    static DateBaseConnection* getInstance(
        std::string dbname,
        std::string host,
        std::string user,
        std::string password
    );

    pqxx::connection* _db;
};

class AuthServer
{
    std::string _loggerLevel;
    ip::tcp::acceptor _acceptor;
    ip::tcp::socket _socket;

    std::string _dbname;
    std::string _host;
    std::string _user;
    std::string _password;

    void acceptAndRun();
    void initServer();
    void getConfFile();
    void initLogger();
    void setLoggerLevel();
public:
    AuthServer(boost::asio::io_service& io_service, uint16_t port):
        _acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)),
        _socket(io_service)
    {
        initServer();
        acceptAndRun();
        DateBaseConnection* responsesHandler = DateBaseConnection::getInstance(
            _dbname,
            _host,
            _user,
            _password
        );
    };
    ~AuthServer() {};
};

#endif // !AUTH_SERVER_NOSOOL