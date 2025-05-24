#include "database.h"
#include <iostream>

sqlite3* connect_to_db(const std::string& db_name) {
    sqlite3* db;
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << "\n";
        return nullptr;
    }
    return db;
}

void execute_query(sqlite3* db, const std::string& query, int (*callback)(void*, int, char**, char**), void* data) {
    char* errMsg = 0;
    if (sqlite3_exec(db, query.c_str(), callback, data, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

void insert_blob(sqlite3* db, const std::string& table, const std::string& column, const std::string& data_column, const std::string& data_value, const std::vector<char>& blob_data) {
    sqlite3_stmt* stmt;
    std::string sql = "INSERT INTO " + table + " (" + data_column + ", " + column + ") VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, data_value.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, blob_data.data(), blob_data.size(), SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Insert failed: " << sqlite3_errmsg(db) << "\n";
        }
        sqlite3_finalize(stmt);
    }
}

std::vector<char> retrieve_blob(sqlite3* db, const std::string& table, const std::string& column, const std::string& condition) {
    std::vector<char> blob;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT " + column + " FROM " + table + " WHERE " + condition + ";";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const void* blob_data = sqlite3_column_blob(stmt, 0);
            int blob_size = sqlite3_column_bytes(stmt, 0);
            blob.assign(static_cast<const char*>(blob_data), static_cast<const char*>(blob_data) + blob_size);
        }
        sqlite3_finalize(stmt);
    }
    return blob;
}
