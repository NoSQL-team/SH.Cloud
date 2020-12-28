cmake_minimum_required(VERSION 3.13.4)
project(ServerFriends)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lpqxx -lpq")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

if(UNIX AND APPLE)
    set(LINUX TRUE)
else()
    set(LINUX FALSE)
endif()

option(test_build "" OFF)

if (LINUX)
    set(CMAKE_CXX_FLAGS "-Wall -lpthread -lboost_thread")
endif()
if (APPLE)
    set(CMAKE_CXX_FLAGS " -lgtest -DBOOST_LOG_DYN_LINK")
endif()



find_package(Boost REQUIRED COMPONENTS system thread regex log_setup log)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_LOG_LIBRARY})
add_definitions(-DBOOST_LOG_DYN_LINK)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(INC_DIR ${DIR}/include)

set(SRC_DIR ${DIR}/src)

set(TESTS_DIR ${DIR}/tests)


include_directories(${INC_DIR}/)
#include_directories(${TESTS_DIR}/)

add_library(server_friends STATIC
        ${SRC_DIR}/utility.cpp
        ${SRC_DIR}/session.cpp
        ${SRC_DIR}/friends_data_base.cpp
        ${SRC_DIR}/server_friends.cpp
        ${SRC_DIR}/request_handler.cpp)

target_link_directories(server_friends PUBLIC include/)

# Server-friends
add_executable(server_friends_test
        server_friends_test.cpp)

target_link_libraries(server_friends_test server_friends ${USED_LIBS} ${PQXX_LIB} ${PQ_LIB})

if(FALSE)

    # Echo-сервер для отладки
    add_executable(echo_server
            echo_server_for_tests.cpp)

    # Клиент для отладки
    add_executable(client
            client_for_tests.cpp)

    target_link_libraries(echo_server ${USED_LIBS})

    target_link_libraries(client ${USED_LIBS})

    find_package(GTest REQUIRED)

    include_directories("${GTEST_INCLUDE_DIRS}")

    # Test базы данных
    add_executable(bd_test
            test_bd.cpp)

    # Unit тесты
    add_executable(TESTS
            tests/tests.cpp)

    add_executable(TESTS_BD
            tests/test_with_bd.cpp)


    target_link_libraries(bd_test ${USED_LIBS} server_friends ${PQXX_LIB} ${PQ_LIB})

    target_include_directories(TESTS PUBLIC ${INC_DIR})

    target_include_directories(TESTS PUBLIC ${TESTS_DIR})

    target_link_libraries(TESTS ${GTEST_LIBRARIES} Threads::Threads pthread server_friends)


    target_include_directories(TESTS_BD PUBLIC ${INC_DIR})

    target_include_directories(TESTS_BD PUBLIC ${TESTS_DIR})

    target_link_libraries(TESTS_BD ${GTEST_LIBRARIES} Threads::Threads pthread server_friends)

    enable_testing()
    add_test(NAME TEST_ONE COMMAND tests1)
endif()