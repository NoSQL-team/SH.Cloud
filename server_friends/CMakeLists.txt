cmake_minimum_required(VERSION 3.9.2)
project(tests CXX)


set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "-g -Wall -O3 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-g -Wall -lpthread -lgtest -L/usr/local/lib -lpqxx -lpq")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


find_package(Boost 1.74.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})


set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(INC_DIR ${DIR}/include)

set(SRC_DIR ${DIR}/src)

set(TESTS_DIR ${DIR}/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(include/)
include_directories(tests/)

add_library(server_friends STATIC
        ${SRC_DIR}/utility.cpp
        ${SRC_DIR}/session.cpp
        ${SRC_DIR}/friends_data_base.cpp
        ${SRC_DIR}/server_friends.cpp
        ${SRC_DIR}/request_handler.cpp)

# Unit тесты
add_executable(TESTS
        tests/tests.cpp
        ${TESTS_DIR}/mock_classes.h)

# Server-friends
add_executable(server_friends_test
        server_friends_test.cpp)

# Echo-сервер для отладки
add_executable(echo_server
        echo_server_for_tests.cpp)

target_link_libraries(server_friends_test ${USED_LIBS} server_friends)

target_link_libraries(echo_server ${USED_LIBS})

target_include_directories(TESTS PUBLIC ${INC_DIR})

target_include_directories(TESTS PUBLIC ${TESTS_DIR})

target_link_libraries(TESTS ${GTEST_LIBRARIES} Threads::Threads pthread server_friends -lgmock)

enable_testing()
add_test(NAME TEST_ONE COMMAND tests1)