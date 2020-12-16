//
// Created by lerakrya on 16.12.2020.
//

#include "Database.h"

void Database::insert_() {
    pqxx::work W(database_);
    W.exec(sql_request);
    W.commit();
}

//pqxx::result Database::select_() {
//    pqxx::nontransaction N(database_);
//    return pqxx::result R( N.exec( sql_request ));
//}

