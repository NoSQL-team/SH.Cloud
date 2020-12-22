//
// Created by lerakrya on 16.12.2020.
//

#include "Database.h"

void Database::insert_(std::string& request) {
    pqxx::connection con("dbname=users host=localhost user=lera password=password port=27003");
    pqxx::work W(con);
    W.exec(request);
    W.commit();
    con.disconnect();
}

pqxx::result Database::select_(std::string& request) {
    pqxx::connection con("dbname=users host=localhost user=lera password=password port=27003");
    pqxx::nontransaction N(con);
    pqxx::result R (N.exec( request ));
    N.commit();
    con.disconnect();
    return R;
}

