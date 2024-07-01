/*
 * world_of_warcraft_prepare.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/27/2024
 */

#include <iostream>
#include <string>
#include <cassert>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW3_WORLD_OF_WARCRAFT_PREPARE_H
#define HW3_WORLD_OF_WARCRAFT_PREPARE_H

#define WARRIOR_NUM 5

enum Color {
    red,
    blue
};

enum Warrior {
    dragon, // = 0
    ninja, // = 1
    iceman, // = 2
    lion, // = 3
    wolf // = 4
};


/**
 * Class to generate warriors
 * */

class Commander {
    const static std::string WARRIOR_NAMES[ WARRIOR_NUM ]; // global warrior names
    const static char* OUTPUT_FORMAT;

    const Color c; // color
    int m; // total life points
    const int *W_n; // local warrior names
    const unsigned *M; // Warrior life points
    unsigned int n = 0; // warrior total count
    unsigned int C[ WARRIOR_NUM ] = { 0 }; // warrior count
    int idx = -1; // warrior index
    bool is_stopped = false;

public:
    Commander( Color c, const int *W ) : c( c ), W_n( W ) {}

    /**
     * Can this commander generate next warrior?
     *
     * @return An index to that warrior is returned if it can, otherwise -1 is returned.
     * */

    int hasNext();

    /**
     * Generate a warrior if this commander can do it.
     *
     * @param t Timestamp string in the format of "XXX"
     * */

    void generate( std::string &t );

    /**
     * Initialize resources.
     *
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void initResource( int m, const unsigned *M );
};

/**
 * Class to coordinate the game.
 * */

class WorldOfWarcraft {
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    unsigned int c = 0; // timestamp count
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE ); // blue headquarter

    static std::string getTimeStr( unsigned int c );

public:
    /**
     * Start the game.
     *
     * @param n Case number.
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void start( unsigned int n, unsigned int m, const unsigned int *M );
};

void caller();

#endif //HW3_WORLD_OF_WARCRAFT_PREPARE_H
