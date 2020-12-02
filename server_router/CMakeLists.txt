cmake_minimum_required(VERSION 3.9.2)
project(tests CXX)


set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-g -Wall -lpthread -lgtest -L/usr/local/lib")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

find_package(Boost 1.74.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

set(nlohmann_json_DIR "/Users/andrewkireev/json")

find_package(nlohmann_json REQUIRED)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(INC_DIR ${DIR}/include)

set(SRC_DIR ${DIR}/src)

set(TESTS_DIR ${DIR}/tests)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(include/)
include_directories(${nlohmann_json_DIR}/include/)
include_directories(tests/)

# Server-router library
add_library(server_router STATIC
        ${SRC_DIR}/utility.cpp
        ${SRC_DIR}/session.cpp
        ${SRC_DIR}/server_router.cpp)

target_link_libraries(server_router
        PRIVATE nlohmann_json::nlohmann_json -I/usr/local/homebrew/Cellar/nlohmann_json/3.9.1/include)

add_executable(TESTS
        ${TESTS_DIR}/tests.cpp
        ${TESTS_DIR}/mock_classes.h)

add_executable(server_router_test
        server_router_for_tests.cpp)

add_executable(test_parser
        test_parser.cpp)


# Эхо сервер для теста роутинга запросов с rout-сервера
add_executable(echo_server
        echo_server_for_tests.cpp)

# Router-server
target_include_directories(server_router_test PUBLIC ${INC_DIR})

target_include_directories(server_router_test PUBLIC ${TESTS_DIR})

target_link_libraries(server_router_test ${USED_LIBS} server_router)

target_link_libraries(test_parser ${USED_LIBS})


# Echo-server
target_link_libraries(echo_server ${USED_LIBS})

# Тесты
target_include_directories(TESTS PUBLIC ${INC_DIR})

target_include_directories(TESTS PUBLIC ${TESTS_DIR})

target_link_libraries(TESTS ${GTEST_LIBRARIES} Threads::Threads pthread server_router -lgmock)

enable_testing()
add_test(NAME TEST_ONE COMMAND tests1)