#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>

sqlite3* connect_to_db(const std::string& db_name);
void execute_query(sqlite3* db, const std::string& query, int (*callback)(void*, int, char**, char**)=nullptr, void* data=nullptr);
void insert_blob(sqlite3* db, const std::string& table, const std::string& column, const std::string& data_column, const std::string& data_value, const std::vector<char>& blob_data);
std::vector<char> retrieve_blob(sqlite3* db, const std::string& table, const std::string& column, const std::string& condition);

#endif // DATABASE_H
