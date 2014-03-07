PROJECT(TP)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "-fpermissive")
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -fpermissive")
SET(CTEST_MEMORYCHECK_COMMAND "/usr/bin/valgrind")

ADD_SUBDIRECTORY(ricp/src)
ADD_SUBDIRECTORY(htmlcxx)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)