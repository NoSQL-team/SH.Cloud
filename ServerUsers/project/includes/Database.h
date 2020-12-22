//
// Created by lerakrya on 11.12.2020.
//

#ifndef SERVERUSERS_DATABASE_H
#define SERVERUSERS_DATABASE_H

#include <string>
#include <map>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <pqxx/pqxx>

class Database {
public:
    Database() {
    	std::string setting = "dbname=users host=localhost user=lera password=password port=27003";
		try {
			database_ = std::make_unique<pqxx::connection>(setting);
		} catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << "Connecting!" << std::endl;
    }
    virtual ~Database() {}
    void insert_(std::string& request);
    pqxx::result select_(std::string& request);

protected:
    std::unique_ptr<pqxx::connection> database_;
};

#endif //SERVERUSERS_DATABASE_H
