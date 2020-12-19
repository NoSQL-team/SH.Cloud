#include "auth-server.hpp"

#include <iostream>
#include <thread>
#include <chrono>

// std::unique_ptr<DateBaseConnection> DateBaseConnection::_objPtr = std::make_unique<DateBaseConnection>(nullptr);
std::mutex DateBaseConnection::_mutex;

DateBaseConnection* DateBaseConnection::getInstance()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _objPtr.get();
}

DateBaseConnection::DateBaseConnection(
    std::string dbname,
    std::string host,
    std::string user,
    std::string password
) {
    std::stringstream ss;
    ss << "dbname=" << dbname << " host=" << host << " user=" << user << " password=" << password << " port=27001";
    while (true) {
        try {
            _db = std::make_unique<pqxx::connection>(ss.str());
            break;
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    std::cout << "Connecting!" << std::endl;
}

DateBaseConnection *DateBaseConnection::getInstance(
    std::string dbname,
    std::string host,
    std::string user,
    std::string password
) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_objPtr == nullptr)
    {
        _objPtr = std::make_unique<DateBaseConnection>(
            dbname,
            host,
            user,
            password
        );
    }
    return _objPtr.get();
}

void DateBaseConnection::dbRequest() {
    std::lock_guard<std::mutex> lock(_mutex);
    pqxx::work w(*_db);
    std::stringstream request;
}

pqxx::result DateBaseConnection::select(
    const std::string& table,
    const std::vector<std::string>& columns,
    const std::vector<std::tuple<std::string, std::string, std::string>>& where
) {
    std::lock_guard<std::mutex> lock(_mutex);
    pqxx::work w(*_db);
    std::stringstream request;
    size_t colQuant = columns.size();

    request << "SELECT ";
    for (const auto& column : columns) {
        request << column << (colQuant - 1 == &column  - &columns[0] ? " " : ", ");
    }
    request << "FROM " << table << " ";
    if (!where.empty()) {
        request << "WHERE ";
        for (const auto& whereEntry : where) {
            request << 
                get<0>(whereEntry) << 
                "=" <<
                (get<2>(whereEntry) == "number" ? "" : "\'") <<
                get<1>(whereEntry) <<
                (get<2>(whereEntry) == "number" ? "" : "\'") <<
                ", ";
        }
        request.seekp(-2, std::ios_base::end);
        request << '\0';
    }

    pqxx::result r = w.exec(request.str());
    w.commit();
    return r;
}

pqxx::result DateBaseConnection::update(
    const std::string& table,
    const std::vector<std::tuple<std::string, std::string, std::string>>& columnsValue,
    const std::vector<std::tuple<std::string, std::string, std::string>>& where
) {
    std::lock_guard<std::mutex> lock(_mutex);
    pqxx::work w(*_db);
    std::stringstream request;

    request << "UPDATE " << table << " SET ";
    for (const auto& columnValue : columnsValue) {
        request << 
            get<0>(columnValue) << 
            "=" <<
            (get<2>(columnValue) == "number" ? "" : "\'") <<
            get<1>(columnValue) <<
            (get<2>(columnValue) == "number" ? "" : "\'") <<
            ", ";
    }
    request.seekp(-2, std::ios_base::end);
    request << '\0' << " ";

    if (!where.empty()) {
        request << "WHERE ";
        for (const auto& whereEntry : where) {
            request << 
                get<0>(whereEntry) << 
                "=" <<
                (get<2>(whereEntry) == "number" ? "" : "\'") <<
                get<1>(whereEntry) <<
                (get<2>(whereEntry) == "number" ? "" : "\'") <<
                ", ";
        }
        request.seekp(-2, std::ios_base::end);
        request << '\0';
    }

    pqxx::result r = w.exec(request.str());
    w.commit();
    return r;
}

pqxx::result DateBaseConnection::insert(
    const std::string& table,
    const std::vector<std::tuple<std::string, std::string, std::string>>& columnsValue
) {
    std::lock_guard<std::mutex> lock(_mutex);
    pqxx::work w(*_db);
    std::stringstream request;

    request << "INSERT INTO " << table << " (";
    for (const auto& columnValue : columnsValue) {
        request << get<0>(columnValue) << ", ";
    }
    request.seekp(-2, std::ios_base::end);
    request << ") VALUES (";
    for (const auto& columnValue : columnsValue) {
        request <<
            (get<2>(columnValue) == "number" ? "" : "\'") <<
            get<1>(columnValue) <<
            (get<2>(columnValue) == "number" ? "" : "\'") <<
            ", ";
    }
    request.seekp(-2, std::ios_base::end);
    request << ")";

    pqxx::result r = w.exec(request.str());
    w.commit();
    return r;
}
