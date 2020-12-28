cmake_minimum_required(VERSION 3.13.4)
project(ServerUsers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lpqxx -lpq")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost REQUIRED COMPONENTS system thread regex log_setup log)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_LIBRARIES})
add_definitions(-DBOOST_LOG_DYN_LINK)

set(INC_DIR ${DIR}includes)

set(SRC_DIR ${DIR}src)

set(TESTS_DIR ${DIR}tests)

include_directories(includes/)

add_library(ServerUsers STATIC ${SRC_DIR}/Session.cpp ${SRC_DIR}/HandlerUser.cpp
        ${INC_DIR}/Session.h ${SRC_DIR}/Server.cpp ${INC_DIR}/HandlerUser.h
        ${INC_DIR}/UsersDatabase.h
        ${SRC_DIR}/Database.cpp
        ${INC_DIR}/Server.h ${SRC_DIR}/UsersDatabase.cpp)


target_link_directories(ServerUsers PUBLIC includes/)

add_executable(test_parser main.cpp)

add_executable(http_echo_server http_echo_server.cpp)

add_executable(echo_server echo_server.cpp)

add_executable(test_server test_server.cpp)

add_executable(client client.cpp)
target_include_directories(test_parser PUBLIC includes/)

add_executable(test_db test_db.cpp)

target_link_libraries(test_parser ${USED_LIBS} ServerUsers)

target_link_libraries(test_server ${USED_LIBS} ServerUsers)


target_link_libraries(ServerUsers ${USED_LIBS})

target_link_libraries(test_db ServerUsers)

target_link_libraries(echo_server ${USED_LIBS})

target_link_libraries(http_echo_server ${USED_LIBS})

target_link_libraries(client ${USED_LIBS})