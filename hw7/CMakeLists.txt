cmake_minimum_required(VERSION 3.22)
project(hw7)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        hw7 main.cpp

#        src/simple_sumarray.cpp
#        include/simple_sumarray.h

        src/simple_foreach.cpp
        include/simple_foreach.h
)
