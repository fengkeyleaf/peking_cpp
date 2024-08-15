cmake_minimum_required(VERSION 3.22)
project(final)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        final main.cpp

#        src/wow_weapons.cpp
#        include/wow_weapons.h

        include/my_iostream.h
        include/my_assert.h
        src/my_assert.cpp
        include/my_logging.h
        src/my_logging.cpp

        include/config.h
        src/config.cpp
        src/warrior.cpp
        include/warrior.h
        src/weapon.cpp
        include/weapon.h
        src/commander.cpp
        include/commander.h
        src/city.cpp
        include/city.h

        include/wow_war.h
        src/wow_war.cpp

        src/tester.cpp
        include/tester.h
)
