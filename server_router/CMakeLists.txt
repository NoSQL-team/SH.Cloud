cmake_minimum_required(VERSION 3.9.2)
project(tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_USE_MULTITHREAD ON)

set(CMAKE_CXX_FLAGS "-Wall -lpthread -lboost_thread -lgtest -L/usr/local/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

find_package(Boost REQUIRED COMPONENTS system thread regex)
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

# Server-router library
add_library(server_router STATIC
        ${SRC_DIR}/utility.cpp
        ${SRC_DIR}/session.cpp
        ${SRC_DIR}/server_router.cpp)


add_executable(TESTS
        ${TESTS_DIR}/tests.cpp)

# Исполняймый файл для теста Router-servera
add_executable(server_router_test
        server_router_for_tests.cpp)

# Исполняймый файл для теста парсера
add_executable(test_parser
        test_parser.cpp)


# Эхо серверы для теста роутинга запросов с rout-сервера
add_executable(echo_server_1
        echo_server_for_tests_1.cpp)

add_executable(echo_server_2
        echo_server_for_tests_2.cpp)

add_executable(client_test
        client_for_tests.cpp)

# Router-server
target_include_directories(server_router_test PUBLIC ${INC_DIR})

target_include_directories(server_router_test PUBLIC ${TESTS_DIR})

target_link_libraries(server_router_test ${USED_LIBS} server_router)

target_link_libraries(test_parser ${USED_LIBS} server_router)

target_link_libraries(test_parser ${USED_LIBS})


# Echo-servers
target_link_libraries(echo_server_1 ${USED_LIBS})
target_link_libraries(echo_server_2 ${USED_LIBS})

# Тесты
target_include_directories(TESTS PUBLIC ${INC_DIR})

target_include_directories(TESTS PUBLIC ${TESTS_DIR})

target_link_libraries(TESTS ${GTEST_LIBRARIES} Threads::Threads pthread server_router)

enable_testing()
add_test(NAME TEST_ONE COMMAND tests1)