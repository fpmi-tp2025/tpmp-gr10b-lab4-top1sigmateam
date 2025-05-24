#include <CUnit/Basic.h>
     #include <CUnit/CUnit.h>

     // Объявление внешних тестовых наборов
     extern CU_SuiteInfo auth_suite[];
     extern CU_SuiteInfo database_suite[];

     int main() {
         if (CUE_SUCCESS != CU_initialize_registry()) {
             return CU_get_error();
         }

         // Регистрация тестовых наборов
         CU_SuiteInfo suites[] = {
             auth_suite[0], // Первый элемент массива auth_suite
             database_suite[0], // Первый элемент массива database_suite
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
