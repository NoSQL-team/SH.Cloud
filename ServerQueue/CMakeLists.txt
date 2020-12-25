cmake_minimum_required(VERSION 3.13.4)
project(ServerQueue)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-Wall -lpthread -lboost_thread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


find_package(Boost 1.65.1 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})




set(INC_DIR ${DIR}/includes)

set(SRC_DIR ${DIR}/src)

set(TESTS_DIR ${DIR}/tests)

include_directories(includes/)

add_library(server_queue STATIC src/Server.cpp src/Session.cpp
        project/includes/Server.h includes/Session.h)

add_executable(echo_server echo_server.cpp)

add_executable(client client.cpp)

add_executable(ServerQueue main.cpp)

target_link_libraries(ServerQueue ${USED_LIBS} server_queue)

target_link_libraries(echo_server ${USED_LIBS})

target_link_libraries(client ${USED_LIBS})
