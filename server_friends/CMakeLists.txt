cmake_minimum_required(VERSION 3.9.2)
project(tests CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-g -Wall -O3 -lgmock")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)



set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(INC_DIR ${DIR}/include)

set(SRC_DIR ${DIR}/src)

set(TESTS_DIR ${DIR}/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(include/)

add_library(server_friends SHARED
        ${INC_DIR}/utilty.h
        ${INC_DIR}/connection.h
        ${INC_DIR}/server_friends.h
        ${INC_DIR}/friends_data_base.h
        ${SRC_DIR}/server_friends.cpp)

add_executable(TESTS
        tests/tests.cpp)

target_include_directories(TESTS PUBLIC ${INC_DIR})

target_link_libraries(TESTS ${GTEST_LIBRARIES} Threads::Threads server_friends)