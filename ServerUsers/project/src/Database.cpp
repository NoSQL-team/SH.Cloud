//
// Created by lerakrya on 16.12.2020.
//

#include "Database.h"

void Database::insert_(std::string& request) {
    pqxx::work W(database_);
    W.exec(request);
    W.commit();
}

pqxx::result Database::select_(std::string& request) {
    pqxx::nontransaction N(database_);
    return pqxx::result R( N.exec( request ));
}

