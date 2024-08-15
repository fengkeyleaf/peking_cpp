/*
 * config.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include <string>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_CONFIG_H
#define FINAL_CONFIG_H

// -------------------------------------------------------
// Marco
// -------------------------------------------------------

#define WARRIOR_NUM 5
#define WEAPON_NUM 3
#define MAX_CITY_NUM 20 // Excluding city 0 and city N + 1

// -------------------------------------------------------
// Global variables
// -------------------------------------------------------

extern const char *COLOR_NAMES[];
extern const char *WEAPON_NAMES[];
extern const std::string WARRIOR_NAMES[]; // global warrior names

// -------------------------------------------------------
// enum types
// -------------------------------------------------------

enum Color_enum {
    red,
    blue
};

enum Warrior_enum {
    dragon, // = 0
    ninja, // = 1
    iceman, // = 2
    lion, // = 3
    wolf // = 4
};

enum Weapon_enum {
    sword, // 0
    bomb, // 1
    arrow // 2
};

#endif //FINAL_CONFIG_H
