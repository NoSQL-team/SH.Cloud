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
    DateBaseConnection() {};
    ~DateBaseConnection() {};
    std::string select(std::string request);
    size_t add_entry(std::string entry);
    size_t delete_entry(std::string request);
};

class parserJSON
{
private:
    
public:
    parserJSON() {};
    ~parserJSON() {};
    std::map<std::string, std::string> parse(std::string str);
    std::string jsonfication(std::map<std::string, std::string> object);
};

class Connection
{
private:

public:
    Connection() {};
    ~Connection() {};
};

class AuthService
{
private:
    DateBaseConnection _dbConn;
    parserJSON _JSONparser;
    std::string requestHandlerIsAuth(std::string body);
    std::string requestHandlerAuth(std::string body);
    std::string requestHandlerLogout(std::string body);
    std::string requestHandlerAddUser(std::string body);
    std::string genToken(std::string nick, std::string email);
    void sendResponse();
    std::string getRequest();
public:
    AuthService() {};
    void run();
    void setServerHTTP(std::string port, std::string ip);
    void setServerQueue(std::string port, std::string ip);
};

#endif // AUTH_SERVER_NOSOOL