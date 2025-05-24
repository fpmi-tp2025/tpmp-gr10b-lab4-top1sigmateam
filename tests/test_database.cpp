#include <CUnit/Basic.h>
   #include "../includes/database.h"
   #include <vector>
   #include <fstream>
   #include <string>

   static sqlite3* db;

   static int init_suite(void) {
       db = connect_to_db("database.db");
       if (!db) return -1;
       std::ifstream sql_file("setup.sql");
       std::string sql((std::istreambuf_iterator<char>(sql_file)), std::istreambuf_iterator<char>());
       execute_query(db, sql, nullptr, nullptr);
       return 0;
   }

   static int clean_suite(void) {
       if (db) sqlite3_close(db);
       db = nullptr;
       return 0;
   }

   static void test_insert_blob(void) {
       std::vector<char> blob_data = { 'd', 'a', 't', 'a' };
       insert_blob(db, "Products", "image", "name", "Test Image", blob_data);
       std::vector<char> retrieved = retrieve_blob(db, "Products", "image", "name = 'Test Image'");
       CU_ASSERT_EQUAL(blob_data.size(), retrieved.size());
       for (size_t i = 0; i < blob_data.size(); ++i) {
           CU_ASSERT_EQUAL(blob_data[i], retrieved[i]);
       }
   }

   static void test_execute_query(void) {
       execute_query(db, "INSERT INTO Brokers (last_name, address, birth_year) VALUES ('Test', 'Test Address', 1990);", nullptr, nullptr);
       sqlite3_stmt* stmt;
       const char* sql = "SELECT COUNT(*) FROM Brokers WHERE last_name = 'Test';";
       if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
           if (sqlite3_step(stmt) == SQLITE_ROW) {
               CU_ASSERT_EQUAL(sqlite3_column_int(stmt, 0), 1);
           }
           sqlite3_finalize(stmt);
       }
   }

   static void test_retrieve_blob_empty(void) {
       std::vector<char> retrieved = retrieve_blob(db, "Products", "image", "name = 'Nonexistent'");
       CU_ASSERT_TRUE(retrieved.empty());
   }

   CU_TestInfo database_tests[] = {
       { "test_insert_blob", test_insert_blob },
       { "test_execute_query", test_execute_query },
       { "test_retrieve_blob_empty", test_retrieve_blob_empty },
       CU_TEST_INFO_NULL,
   };

   CU_SuiteInfo database_suite[] = {
       { "Database Suite", init_suite, clean_suite, NULL, NULL, database_tests },
       CU_SUITE_INFO_NULL,
   };
