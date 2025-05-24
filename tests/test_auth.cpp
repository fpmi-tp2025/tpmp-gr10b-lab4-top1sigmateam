#include <CUnit/Basic.h>
     #include "../includes/auth.h"
     #include "../includes/database.h"

     static sqlite3* db;

     static int init_suite(void) {
         db = connect_to_db("database.db");
         if (!db) return -1;
         execute_query(db, "INSERT OR IGNORE INTO users (username, password, role) VALUES ('admin', 'admin123', 'admin');", nullptr, nullptr);
         return 0;
     }

     static int clean_suite(void) {
         if (db) sqlite3_close(db);
         db = nullptr;
         return 0;
     }

     static void test_authenticate_success(void) {
         CU_ASSERT_TRUE(authenticate(db, "admin", "admin123"));
     }

     static void test_authenticate_failure(void) {
         CU_ASSERT_FALSE(authenticate(db, "admin", "wrongpass"));
     }

     static void test_authenticate_nonexistent_user(void) {
         CU_ASSERT_FALSE(authenticate(db, "nonexistent", "password"));
     }

     CU_TestInfo auth_tests[] = {
         { "test_authenticate_success", test_authenticate_success },
         { "test_authenticate_failure", test_authenticate_failure },
         { "test_authenticate_nonexistent_user", test_authenticate_nonexistent_user },
         CU_TEST_INFO_NULL,
     };

     CU_SuiteInfo auth_suite[] = {
         { "Auth Suite", init_suite, clean_suite, NULL, NULL, auth_tests },
         CU_SUITE_INFO_NULL,
     };
