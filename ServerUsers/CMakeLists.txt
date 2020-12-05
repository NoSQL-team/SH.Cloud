cmake_minimum_required(VERSION 3.17)
project(ServerUsers)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lpqxx -lpq")

find_package(Boost 1.65.1 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(ServerUsers main.cpp project/src/Session.cpp project/src/HandlerUser.cpp project/includes/Session.h project/src/Server.cpp project/includes/HandlerUser.h project/src/UsersDatabase.cpp project/includes/UsersDatabase.h project/includes/Server.h)

add_executable(test_parser main.cpp project/src/UsersDatabase.cpp)
target_include_directories(test_parser PUBLIC project/includes/UsersDatabase.h)

target_link_libraries(test_parser ${USED_LIBS})

target_link_libraries(ServerUsers ${USED_LIBS})