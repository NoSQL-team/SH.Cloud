cmake_minimum_required(VERSION 3.13.4)

project(boost-asio-examples)
#======================================================================================

option(TESTS "" OFF)

#======================================================================================

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "-lpthread -lgtest")

#======================================================================================

find_package(Boost 1.67.0 REQUIRED COMPONENTS system thread regex log_setup log)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_LIBRARIES})
add_definitions(-DBOOST_LOG_DYN_LINK)

#======================================================================================

add_library(libhttp-server STATIC 
  lib/http-server/requests-handler.cpp
  lib/http-server/responses-handler.cpp
  lib/http-server/http-server.cpp
  lib/http-server/session.cpp
)

if(TESTS)
  find_package(GTest REQUIRED)
  find_package(Threads REQUIRED)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED on)

  add_executable(mainTest 
    tests/tests.cpp
    tests/mock_classes.h
  )

  include_directories(${GTEST_INCLUDE_DIRS})
  target_link_libraries(
      mainTest  
      ${GTEST_LIBRARIES} 
      Threads::Threads
      ${USED_LIBS} 
      libhttp-server
      -lgmock
  )

else()
  add_executable(main main.cpp)
  target_link_libraries(main ${USED_LIBS} libhttp-server -lboost_iostreams)
endif()
