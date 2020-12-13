cmake_minimum_required(VERSION 3.17)
project(ServerQueue)

set(CMAKE_CXX_STANDARD 17)


find_package(Boost 1.65.1 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})




set(INC_DIR ${DIR}/project/includes)

set(SRC_DIR ${DIR}/project/src)

set(TESTS_DIR ${DIR}/tests)

include_directories(project/includes/)

add_library(server_queue STATIC project/src/Server.cpp project/src/Session.cpp
        project/includes/Server.h project/includes/Session.h)

add_executable(echo_server echo_server.cpp)

add_executable(client client.cpp)

add_executable(test_server main.cpp)

target_link_libraries(test_server ${USED_LIBS} server_queue)

target_link_libraries(echo_server ${USED_LIBS})

target_link_libraries(client ${USED_LIBS})

add_executable(ServerQueue main.cpp)