cmake_minimum_required(VERSION 3.22)
project(hw3)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        hw3 main.cpp

#        src/big_base.cpp
#        include/big_base.h

        src/where_is_ptr.cpp
        include/where_is_ptr.h

#        src/world_of_warcraft_prepare.cpp
#        include/world_of_warcraft_prepare.h
)
