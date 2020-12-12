#ifndef AUTH_SERVER_NOSOOL
#define AUTH_SERVER_NOSOOL

#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

#include <pqxx/pqxx>

using namespace boost;
using namespace boost::system;
using namespace boost::asio;

class RequestsHandler
{
    std::string _type;
    boost::property_tree::ptree _ptRequest;
    boost::property_tree::ptree _ptResponse;

    //Так как таблица одна незачем делаеть ещё один класс, как модель пользователя или т. п.
    std::string _userPassword;
    std::string _userName;
    std::string _refreshToken;
    std::string _accessToken;

    std::string authRequest();
    std::string auth();
    std::string logout();
    std::string add();
    std::string refresh();

    void logError(const std::string& log);
    void log(const std::string& log);
    std::string errorAnswer(const std::string& error);
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
    pqxx::result select(
        const std::string& table,
        const std::vector<std::string>& columns,
        const std::vector<std::tuple<std::string, std::string, std::string>>& where={}
    );
    pqxx::result update(
        const std::string& table,
        const std::vector<std::tuple<std::string, std::string, std::string>>& columnValue,
        const std::vector<std::tuple<std::string, std::string, std::string>>& where
    );
    pqxx::result insert(
        const std::string& table,
        const std::vector<std::tuple<std::string, std::string, std::string>>& columnsValue
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