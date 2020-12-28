#include "auth-server.hpp"

#include <boost/log/trivial.hpp>

#include <jwt-cpp/jwt.h>

#include <iostream>

const std::string AUTH_REQUEST = "/api/auth/authRequest/";
const std::string AUTH = "/api/auth/auth/";
const std::string LOGOUT = "/api/auth/logout/";
const std::string ADD = "/api/auth/add/";
const std::string REFRESH = "/api/auth/refresh/";
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
    _ptResponse.put("error", error);
    boost::property_tree::write_json(response, _ptResponse);
    return (response.str() + '\r');
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
                {std::make_tuple("user_id", _user_id, "string")}
            );
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("error", "error");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r.empty()) {
        _ptResponse.put("error", "not found user");
    } else {
        if (r[0][0].c_str() == _accessToken) {
            auto decodeToken = jwt::decode(_accessToken);
            if (decodeToken.get_expires_at() < std::chrono::system_clock::now()) {
                _ptResponse.put("error", "token not valid");
            } else {
                _ptResponse.put("response", "ok");
            }
        } else {
            _ptResponse.put("error", "token not valid");
        }
    }

    boost::property_tree::write_json(response, _ptResponse);
    return (response.str() + '\r');
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
        _ptResponse.put("error", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (!r.empty()) {
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
                _ptResponse.put("error", "error");
                boost::property_tree::write_json(response, _ptResponse);
                return response.str();
            }
        } else {
            _ptResponse.put("error", "Bad password");
        }
    } else {
        _ptResponse.put("error", "Bad creditance");
    }
    boost::property_tree::write_json(response, _ptResponse);
    return (response.str() + '\r');
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
        _ptResponse.put("error", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r.empty()) {
        _ptResponse.put("error", "Not found user");
    } else {
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
            _ptResponse.put("error", "Bad token");
        }
    }

    boost::property_tree::write_json(response, _ptResponse);
    return (response.str() + '\r');
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
        _ptResponse.put("error", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }
    if (r.empty()) {
        try {
            db->insert(
                "users",
                {
                    std::make_tuple("username", _userName, "string"),
                    std::make_tuple("refresh_token", "", "string"),
                    std::make_tuple("access_token", "", "string"),
                    std::make_tuple("user_id", _user_id, "number"),
                    std::make_tuple("password", _userPassword, "string")
                }
            );
            _ptResponse.put("response", "ok");
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            _ptResponse.put("error", "error");
            boost::property_tree::write_json(response, _ptResponse);
            return response.str();
        }
    } else {
        _ptResponse.put("response", "not unique username");
    }
    boost::property_tree::write_json(response, _ptResponse);
    return (response.str() + '\r');
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
                {std::make_tuple("user_id", _userName, "string")}
            );
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        _ptResponse.put("error", "not found user");
        boost::property_tree::write_json(response, _ptResponse);
        return response.str();
    }

    if (r.empty()) {
        _ptResponse.put("error", "not found user");
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
            _ptResponse.put("error", "token not valid");
        }
    }

    boost::property_tree::write_json(response, _ptResponse);
    return (response.str() + '\r');
}

std::string RequestsHandler::getResponse(std::istream& stream)
{
    std::getline(stream, _type);
    boost::property_tree::read_json(stream, _ptRequest);

    try {
        if (_type == AUTH_REQUEST) {
            _user_id = _ptRequest.get<std::string>("user_id");
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
            _user_id = _ptRequest.get<std::string>("user_id");
        } else if (_type == REFRESH) {
            _userName = _ptRequest.get<std::string>("user_id");
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
