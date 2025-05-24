#ifndef AUTH_H
#define AUTH_H

#include <sqlite3.h>
#include <string>

bool authenticate(sqlite3* db, const std::string& username, const std::string& password);

#endif // AUTH_H
