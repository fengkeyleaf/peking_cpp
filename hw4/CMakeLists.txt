cmake_minimum_required(VERSION 3.22)
project(hw4)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        hw4 main.cpp

#        src/my_string.cpp
#        include/my_string.h

#        src/strange_operator_overload.cpp
#        include/strange_operator_overload.h

#        src/surprising_print_out.cpp
#        include/surprising_print_out.h

        src/twoD_array.cpp
        include/twoD_array.h
)
