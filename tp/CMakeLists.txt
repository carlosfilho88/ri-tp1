PROJECT(TP)

cmake_minimum_required(VERSION 2.8)

set (CMAKE_C_FLAGS "-fpermissive")
set (CMAKE_CXX_FLAGS "-fpermissive")

ADD_SUBDIRECTORY(RICP/src)
ADD_SUBDIRECTORY(htmlcxx)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)