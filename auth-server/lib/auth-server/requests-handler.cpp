#include "auth-server.hpp"

#include <boost/log/trivial.hpp>

#include <jwt-cpp/jwt.h>

#include <iostream>

const std::string AUTH_REQUEST = "authRequest";
const std::string AUTH = "auth";
const std::string LOGOUT = "logout";
const std::string ADD = "add";
const std::string REFRESH = "refresh";
const std::string SECRET_KEY = "dwabkU&#BN#*(NP*#*(";

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

std::string RequestsHandler::errorAnswer(const std::string& error) 
{
    std::stringstream response;
    logError("Bad request");
    _ptResponse.put("response", error);
    boost::property_tree::write_json(response, _ptResponse);
    return response.str();
}

std::string RequestsHandler::authRequest()
{
    DateBaseConnection* db = DateBaseConnection::getInstance();
    std::stringstream response;
    pqxx::result r;

    try {
        r = db->select(
                "users", 
                {"access_token", "refresh_token"}, 
                {std::make_tuple("username", _userName, "string")}
            );
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("response", "error");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r.empty()) {
        _ptResponse.put("response", "not found user");
    } else {
        if (r[0][0].c_str() == _accessToken) {
            auto decodeToken = jwt::decode(_accessToken);
            if (decodeToken.get_expires_at() < std::chrono::system_clock::now()) {
                _ptResponse.put("response", "token not valid");
            } else {
                _ptResponse.put("response", "ok");
            }
        } else {
            _ptResponse.put("response", "token not valid");
        }
    }

    boost::property_tree::write_json(response, _ptResponse);
    return response.str();
}

std::string RequestsHandler::auth() 
{
    DateBaseConnection* db = DateBaseConnection::getInstance();
    std::stringstream response;
    pqxx::result r;

    try {
        r = db->select(
                "users", 
                {"password"}, 
                {std::make_tuple("username", _userName, "string")}
            );
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("response", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r[0][0].c_str() == _userPassword) {
        try {
            auto aToken = jwt::create()
                .set_issuer(_userName)
                .set_type("JWS")
                .set_issued_at(std::chrono::system_clock::now())
                .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{360})
                .sign(jwt::algorithm::hs256{SECRET_KEY});

            auto rToken = jwt::create()
                .set_issuer(_userName)
                .set_type("JWS")
                .set_issued_at(std::chrono::system_clock::now())
                .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{9000})
                .sign(jwt::algorithm::hs256{SECRET_KEY});

            db->update(
                "users", 
                {
                    std::make_tuple("refresh_token", rToken, "string"),
                    std::make_tuple("access_token", aToken, "string")
                }, 
                {std::make_tuple("username", _userName, "string")}
            );

            _ptResponse.put("access_token", aToken);
            _ptResponse.put("refresh_token", rToken);
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            _ptResponse.put("response", "error");
            boost::property_tree::write_json(response, _ptResponse);
            return response.str();
        }
    } else {
        _ptResponse.put("response", "Bad password");
    }
    boost::property_tree::write_json(response, _ptResponse);
    return response.str();
}

std::string RequestsHandler::logout() 
{
    DateBaseConnection* db = DateBaseConnection::getInstance();
    std::stringstream response;
    pqxx::result r;

    try {
        r = db->select(
                "users", 
                {"access_token"}, 
                {std::make_tuple("username", _userName, "string")}
            );
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("response", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r[0][0].c_str() == _accessToken) {
        try {
            db->update(
                "users", 
                {
                    std::make_tuple("refresh_token", "", "string"),
                    std::make_tuple("access_token", "", "string")
                }, 
                {std::make_tuple("username", _userName, "string")}
            );
            _ptResponse.put("response", "ok");
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            _ptResponse.put("response", "error");
            boost::property_tree::write_json(response, _ptResponse);
            return response.str();
        }
    } else {
        _ptResponse.put("response", "Bad token");
    }

    boost::property_tree::write_json(response, _ptResponse);
    return response.str();
}

std::string RequestsHandler::add() 
{
    DateBaseConnection* db = DateBaseConnection::getInstance();
    std::stringstream response;
    pqxx::result r;

    try {
        r = db->select(
                "users", 
                {"username"}, 
                {std::make_tuple("username", _userName, "string")}
            );
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("response", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r.empty()) {
        try {
            db->insert(
                "users",
                {
                    std::make_tuple("username", _userName, "string"),
                    std::make_tuple("password", _userPassword, "string")
                }
            );
            _ptResponse.put("response", "ok");
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            _ptResponse.put("response", "error");
            boost::property_tree::write_json(response, _ptResponse);
            return response.str();
        }
    } else {
        _ptResponse.put("response", "not unique username");
    }
    boost::property_tree::write_json(response, _ptResponse);
    return response.str();
}

std::string RequestsHandler::refresh()
{
    DateBaseConnection* db = DateBaseConnection::getInstance();
    std::stringstream response;
    pqxx::result r;

    try {
        r = db->select(
                "users", 
                {"access_token", "refresh_token"}, 
                {std::make_tuple("username", _userName, "string")}
            );
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("response", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r.empty()) {
        _ptResponse.put("response", "not unique username");
    } else {
        if (r[0][1].c_str() == _refreshToken) {
            auto aToken = jwt::create()
                .set_issuer(_userName)
                .set_type("JWS")
                .set_issued_at(std::chrono::system_clock::now())
                .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{360})
                .sign(jwt::algorithm::hs256{SECRET_KEY});
            db->update(
                "users", 
                {
                    std::make_tuple("access_token", aToken, "string")
                }, 
                {std::make_tuple("username", _userName, "string")}
            );
            _ptResponse.put("response", "ok");
            _ptResponse.put("access_token", aToken);
        } else {
            _ptResponse.put("response", "token not valid");
        }
    }

    boost::property_tree::write_json(response, _ptResponse);
    return response.str();
}

std::string RequestsHandler::getResponse(std::istream& stream)
{
    boost::property_tree::read_json(stream, _ptRequest);

    try {
        _type = _ptRequest.get<std::string>("type");
        if (_type == AUTH_REQUEST) {
            _userName = _ptRequest.get<std::string>("username");
            _accessToken = _ptRequest.get<std::string>("access_token");
        } else if (_type == AUTH) {
            _userPassword = _ptRequest.get<std::string>("password");
            _userName = _ptRequest.get<std::string>("username");
        } else if (_type == LOGOUT) {
            _accessToken = _ptRequest.get<std::string>("access_token");
            _userName = _ptRequest.get<std::string>("username");
        } else if (_type == ADD) {
            _userName = _ptRequest.get<std::string>("username");
            _userPassword = _ptRequest.get<std::string>("password");
        } else if (_type == REFRESH) {
            _userName = _ptRequest.get<std::string>("username");
            _refreshToken = _ptRequest.get<std::string>("refresh_token");
        }
    }
    catch(const std::exception& e) {
        return errorAnswer(e.what());
    }

    if (_type == AUTH_REQUEST) {
        log("request with auth");
        return authRequest();    
    } else if (_type == AUTH) {
        log("auth request");
        return auth();
    } else if (_type == LOGOUT) {
        log("logout request");
        return logout();
    } else if (_type == ADD) {
        log("add request");
        return add();
    } else if (_type == REFRESH) {
        log("refresh request");
        return refresh();
    }

    return errorAnswer("error");
}
