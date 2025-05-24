#include "auth.h"
#include <iostream>

bool authenticate(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT role FROM users WHERE username = ? AND password = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::cout << "Authenticated as: " << role << "\n";
            sqlite3_finalize(stmt);
            return true;
        }
        sqlite3_finalize(stmt);
    }
    return false;
}
