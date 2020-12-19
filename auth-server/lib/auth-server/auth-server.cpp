#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include <cstdlib>

#include "auth-server.hpp"

namespace logging = boost::log;

void AuthServer::getConfFile() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("noskoolAuth.ini", pt);
    try {
        _loggerLevel = pt.get<std::string>("logger.level");
        _dbname = pt.get<std::string>("db.dbname");
        _host = pt.get<std::string>("db.host");
        _user = pt.get<std::string>("db.user");
        _password = pt.get<std::string>("db.password");
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

void AuthServer::setLoggerLevel() {
    auto level = logging::trivial::warning;
    if (_loggerLevel == "trace") {
        level = logging::trivial::trace;
    } else if (_loggerLevel == "debug") {
        level = logging::trivial::debug;
    } else if (_loggerLevel == "info") {
        level = logging::trivial::info;
    } else if (_loggerLevel == "error") {
        level = logging::trivial::error;
    } else if (_loggerLevel == "fatal") {
        level = logging::trivial::fatal;
    }
    logging::core::get()->set_filter(
        logging::trivial::severity >= level
    );
}

void AuthServer::initLogger() {
    setLoggerLevel();
}

void AuthServer::initServer() {
    getConfFile();
    initLogger();
}

void AuthServer::acceptAndRun()
{
    _acceptor.async_accept(
        _socket,
        [this](const error_code& accept_error) {
            if(!accept_error) {
                std::make_shared<Session>(std::move(_socket))->start();
            }
            acceptAndRun();
        }
    );
}