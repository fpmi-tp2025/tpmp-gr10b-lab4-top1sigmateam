#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "database.h"
#include "auth.h"

static int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << "\n";
    return 0;
}

int main() {
    sqlite3* db = connect_to_db("database.db");
    if (!db) return 1;

    // Инициализация базы данных
    std::ifstream sql_file("setup.sql");
    std::string sql((std::istreambuf_iterator<char>(sql_file)), std::istreambuf_iterator<char>());
    execute_query(db, sql, nullptr, nullptr);

    // Аутентификация
    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    if (authenticate(db, username, password)) {
        std::cout << "Authenticated successfully!\n";

        // Пример операций с базой данных
        execute_query(db, "SELECT * FROM users;", callback, nullptr);
        execute_query(db, "SELECT p.name, s.name FROM Products p JOIN Suppliers s ON p.supplier_id = s.supplier_id;", callback, nullptr);
        execute_query(db, "UPDATE Brokers SET address = 'ул. Новая, д.10' WHERE last_name = 'Иванов';", nullptr, nullptr);
        execute_query(db, "DELETE FROM Deals WHERE deal_id = 1;", nullptr, nullptr);

        // Вставка изображения
        std::ifstream file("image.jpg", std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);
            std::vector<char> buffer(size);
            file.read(buffer.data(), size);
            insert_blob(db, "Products", "image", "name", "Sample Image", buffer);
            std::cout << "Image inserted successfully!\n";
        }
    } else {
        std::cout << "Authentication failed.\n";
    }

    sqlite3_close(db);
    return 0;
}
