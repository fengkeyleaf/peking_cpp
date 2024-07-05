cmake_minimum_required(VERSION 3.22)
project(hw8)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        hw8 main.cpp

#        src/goodcopy.cpp
#        include/goodcopy.h

#        src/sort_by_distance.cpp
#        include/sort_by_distance.h

        src/tricky_3d_array.cpp
        include/tricky_3d_array.h
        src/function_filter.cpp
        include/function_filter.h
)
