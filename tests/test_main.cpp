#include <CUnit/Basic.h>
     #include <CUnit/CUnit.h>
     #include "test_auth.cpp"
     #include "test_database.cpp"

     int main() {
         if (CUE_SUCCESS != CU_initialize_registry()) {
             return CU_get_error();
         }

         // Регистрация тестовых наборов
         extern CU_SuiteInfo auth_suite[];
         extern CU_SuiteInfo database_suite[];

         CU_SuiteInfo suites[] = {
             { "Auth Suite", NULL, NULL, NULL, NULL, auth_suite },
             { "Database Suite", NULL, NULL, NULL, NULL, database_suite },
             CU_SUITE_INFO_NULL,
         };

         if (CUE_SUCCESS != CU_register_suites(suites)) {
             CU_cleanup_registry();
             return CU_get_error();
         }

         CU_basic_set_mode(CU_BRM_VERBOSE);
         CU_basic_run_tests();
         CU_cleanup_registry();
         return CU_get_error();
     }
