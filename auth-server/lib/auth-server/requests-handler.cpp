#include "auth-server.hpp"

std::string RequestsHandler::getResponse(std::istream& stream)
{
    std::stringstream ssOut;
    ssOut << "12\n" << "\n" << "{\"token\": \"123ewfewsags.esfsef.sefsefsefsef\"}";

    try {
        DateBaseConnection* db = DateBaseConnection::getInstance();
        pqxx::work w(*(db->_db));
        pqxx::result r = w.exec("SELECT * FROM users");
        w.commit();
        for (const auto& n : r) {
            for(const auto& f : n) {
                std::cout << f.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    return ssOut.str();
}
