cmake_minimum_required(VERSION 3.22)
project(hw5)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        hw5 main.cpp

#        src/complete_my_string.cpp
#        include/complete_my_string.h

        src/inherited_my_string.cpp
        include/inherited_my_string.h
)
