cmake_minimum_required(VERSION 3.15.3)
project(ServerUsers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "-g -Wall -O3 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-g -Wall -lpthread -lgtest -L/usr/local/lib -lpqxx -lpq")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)



set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(INC_DIR ${DIR}/project/headers)

set(SRC_DIR ${DIR}/project/src)

set(TESTS_DIR ${DIR}/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(project/headers/)
include_directories(tests/)

add_library(server_users STATIC
        ${SRC_DIR}/Connection.cpp
        ${INC_DIR}/Connection.h
        project/src/SServer.cpp project/src/Socket.cpp project/src/Parser.cpp project/src/ServerUser.cpp)

add_executable(TESTS
        tests/tests_gmock.cpp)

target_include_directories(TESTS PUBLIC ${INC_DIR})

target_include_directories(TESTS PUBLIC ${TESTS_DIR})

target_link_libraries(TESTS ${GTEST_LIBRARIES} Threads::Threads pthread server_users -lgmock)

enable_testing()
add_test(NAME TEST_ONE COMMAND tests1)


#add_executable(ServerUsers main.cpp project/headers/Socket.h project/headers/Connection.h project/headers/SServer.h project/headers/Parser.h project/headers/ServerUser.h tests/test_gmock.cpp.h tests/tests_gmock.cpp)