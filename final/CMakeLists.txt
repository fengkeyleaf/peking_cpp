cmake_minimum_required(VERSION 3.22)
project(final)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        final main.cpp

        src/wow_weapons.cpp
        include/wow_weapons.h
)
