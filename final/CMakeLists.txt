cmake_minimum_required(VERSION 3.22)
project(final)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        final main.cpp

#        src/wow_weapons.cpp
#        include/wow_weapons.h

        include/my_assert.h
        src/my_assert.cpp
        include/wow_war.h
        src/wow_war.cpp
)
