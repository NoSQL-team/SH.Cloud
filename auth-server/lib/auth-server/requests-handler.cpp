#include "auth-server.hpp"

#include <boost/log/trivial.hpp>

#include <iostream>

const std::string IS_AUTH = "isAuth";
const std::string AUTH = "auth";

void RequestsHandler::logError(const std::string& log)
{
    BOOST_LOG_TRIVIAL(error) << log;
    std::cout << " " << std::endl;
}

void RequestsHandler::log(const std::string& log)
{
    BOOST_LOG_TRIVIAL(info) << log;
    std::cout << " " << std::endl;
}

std::string RequestsHandler::errorAnswer(const std::string& error) {
    std::stringstream response;
    logError("Bad request");
    _ptResponse.put("response", error);
    boost::property_tree::write_json(response, _ptResponse);
    return response.str();
}

std::string RequestsHandler::isAuth()
{
    DateBaseConnection* db = DateBaseConnection::getInstance();
    std::stringstream response;
    pqxx::result r;

    try {
        r = db->select(
                "users", 
                {"refresh_token"}, 
                {std::make_tuple("user_id", _userId, "number")}
            );
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("response", "error");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    _ptResponse.put("response", (r[0][0].c_str() != nullptr ? true : false));
    boost::property_tree::write_json(response, _ptResponse);

    return response.str();
}

std::string RequestsHandler::auth() {
    DateBaseConnection* db = DateBaseConnection::getInstance();
    std::stringstream response;
    pqxx::result r;

    try {
        r = db->select(
                "users", 
                {"password", "username", "user_id"}, 
                {std::make_tuple("username", _userName, "string")}
            );
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("response", "not found");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r[0][0].c_str() == _userPassword) {
        try {
            db->update(
                "users", 
                {std::make_tuple("refresh_token", "12", "string")}, 
                {std::make_tuple("username", _userName, "string")}
            );
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        
    }
    return "";
}

std::string RequestsHandler::getResponse(std::istream& stream)
{
    boost::property_tree::read_json(stream, _ptRequest);

    try {
        _type = _ptRequest.get<std::string>("type");
        if (_type == IS_AUTH) {
            _userId = _ptRequest.get<std::string>("userId");
        } else if (_type == AUTH) {
            _userPassword = _ptRequest.get<std::string>("password");
            _userName = _ptRequest.get<std::string>("username");
        }
    }
    catch(const std::exception& e) {
        return errorAnswer(e.what());
    }

    if (_type == IS_AUTH) {
        log("is auth request");
        return isAuth();    
    } else if (_type == AUTH) {
        log("auth request");
        return auth();
    }

    return errorAnswer("error");
}
