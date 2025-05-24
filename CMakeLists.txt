cmake_minimum_required(VERSION 3.10)
project(ConsoleApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

find_library(SQLITE3_LIBRARY NAMES sqlite3)
find_library(CUNIT_LIBRARY NAMES cunit)
include_directories(${CMAKE_SOURCE_DIR}/includes)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
 endif()

 add_executable(app src/main.cpp src/database.cpp src/auth.cpp)
 target_link_libraries(app ${SQLITE3_LIBRARY})

 include(CTest)
 add_executable(tests tests/test_main.cpp tests/test_auth.cpp tests/test_database.cpp src/database.cpp src/auth.cpp)
 target_link_libraries(tests ${SQLITE3_LIBRARY} ${CUNIT_LIBRARY})
 add_test(NAME AllTests COMMAND tests)
