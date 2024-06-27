cmake_minimum_required(VERSION 3.22)
project(hw2)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        hw2 main.cpp

#        src/strange_class_copy.cpp
#        include/strange_class_copy.h

#        src/what_to_return.cpp
#        include/what_to_return.h

#        src/simple_complex.cpp
#        include/simple_complex.h

        src/where_res_comes_from.cpp
        include/where_res_comes_from.h
)
