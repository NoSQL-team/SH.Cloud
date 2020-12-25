//
// Created by lerakry on 04.12.2020.
//

#include "UsersDatabase.h"
#include "pqxx/pqxx"

using std::string;

    UsersDatabase::~UsersDatabase() = default;

    bool UsersDatabase::insert(const std::map<string, string>& users_data, int id_user) {
        if (id_user != -1) {
            return false;
        }

        string sql_request("INSERT INTO users VALUES(DEFAULT, ");
        int i = 0;
        for(auto& data : users_data) {
            if (data.first == "password") {
				continue;
			}
			if (i != 0)
				sql_request += ", ";
			sql_request += "\'" + data.second + "\'";
            i = 1;
        }
        sql_request += ")";

		insert_(sql_request);
		return true;
    }

    string UsersDatabase::data_user(int id) {
        string sql_request = "SELECT * FROM Users WHERE id=";
        sql_request += std::to_string(id);

        pqxx::result R = select_(sql_request);

        string answer = "{\n";
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            answer += "  \"firstname\": \"" + c[1].as<string>() + "\",\n";
            answer += "  \"lastname\": \"" + c[2].as<string>() + "\",\n";
            answer += "  \"nickname\": \"" + c[3].as<string>() + "\",\n";
            answer += "  \"email\": \"" + c[4].as<string>() + "\",\n";
            answer += "  \"photo\": \"" + c[5].as<string>() + "\"";
        }
        answer += "\n}";

        if (answer == "{\n\n}") {
            return "No user";
        }

        return answer;
    }

    string UsersDatabase::all_users(){
        string sql_request("SELECT nickname FROM users");

        pqxx::result R = select_(sql_request);

        string answer = "{\n";

		int i = 0;
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
        	if (i != 0) {
        		answer += ",\n";
        	}
        	i++;
            answer += "  \"nickname\": \"" + c[0].as<string>() + "\"";
        }
        answer += "\n}";

        if (answer == "{\n\n}") {
            return "No users";
        }

        return answer;
    }

    bool UsersDatabase::exist(int id) {
        string sql_request("SELECT id FROM Users WHERE id=");
        sql_request += std::to_string(id);

        pqxx::result R = select_(sql_request);

        string answer = "{\n";

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            answer += "  \"id\": \"" + c[0].as<string>() + "\" ,\n";
        }
        answer += "}";

        if (answer == "{\n}") {
            return false;
        }
        return true;
    }

    std::string UsersDatabase::id_by_nick(std::string& nickname) {
        string sql_request("SELECT id FROM Users WHERE nickname=");
        sql_request += "\'" + nickname + "\'";

        pqxx::result R = select_(sql_request);

        string answer = "{\n";

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            answer += "  \"id\": \"" + c[0].as<string>() + "\"\n";
        }
        answer += "}";

        if (answer == "{\n}") {
            return "No user";
        }
        return answer;
    }

    bool UsersDatabase::update(const std::map<string, string>& data, int id_user) {

        for (const auto& [el, el1] : data) {
            std::cout << el << " " << el1 << std::endl;
        }

        // if (data.at("Aid") != std::to_string(id_user)) {
        //     std::cout << "/* message error*/" << std::endl;
        //     return false;
        // }

        string sql_request("UPDATE users SET ");
        int i = 0;
        for(const auto& v : data) {
            i++;
            if (i == 1)
                continue;
            if (i != 2 ) {
                sql_request += ", ";
            }
            sql_request += v.first.substr(1) + "=\'" + v.second + "\'";
        }
        sql_request += " WHERE id=" + data.at("Aid");
        std::cout << sql_request << std::endl;
        if(exist(atoi(data.at("Aid").c_str())) == false) {
            return false;
        }
        insert_(sql_request);
        return true;
    }

int UsersDatabase::get_id() {
	string sql_request("SELECT MAX(id) FROM Users");

    pqxx::result R;
    string answer;
    int id;

    try {
        R = select_(sql_request);
        if (!R.empty()) {
            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
                answer = c[0].as<string>();
            }
            id = atoi(answer.c_str());
        } else {
            id = 0;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        id = 0;
    }
	return ++id;
}

