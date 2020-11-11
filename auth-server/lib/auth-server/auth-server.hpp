#ifndef AUTH_SERVER_NOSOOL
#define AUTH_SERVER_NOSOOL

#include <string>
#include <map>
#include <pqxx/pqxx>

class DateBaseConnection
{
private:
    pqxx::connection _db;
public:
    DateBaseConnection();
    ~DateBaseConnection();
    std::string select(std::string request);
    size_t add_entry(std::string entry);
    size_t delete_entry(std::string request);
};

class parserJSON
{
private:
    
public:
    parserJSON();
    ~parserJSON();
    std::map<std::string, std::string> parse(std::string str);
};

class Connection
{
private:

public:
    Connection();
    ~Connection();
};

class AuthService
{
private:
    DateBaseConnection _dbConn;
    parserJSON _JSONparser;
public:
    AuthService();
    ~AuthService();
    void sendResponse();
    std::string getRequest();
    void setServerHTTP(std::string port, std::string ip);
    void setServerQueue(std::string port, std::string ip);
};

#endif // AUTH_SERVER_NOSOOL