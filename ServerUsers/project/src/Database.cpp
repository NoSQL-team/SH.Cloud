//
// Created by lerakrya on 16.12.2020.
//

#include "Database.h"

Database::Database() {
	std::string setting = "dbname=users host=localhost user=andrewkireev password=";
	try {
		database_ = std::make_unique<pqxx::connection>(setting);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Connecting!" << std::endl;
}

void Database::insert_(std::string& request) {
    pqxx::work W(*database_);
    W.exec(request);
    W.commit();
}

pqxx::result Database::select_(std::string& request) {
    pqxx::nontransaction N(*database_);
    pqxx::result R (N.exec( request ));
    return R;
}

