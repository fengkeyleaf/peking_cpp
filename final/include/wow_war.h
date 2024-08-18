/*
 * wow_war.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/10/2024
 */

#include "./my_logging.h"
#include "./my_assert.h"
#include "./weapon.h"
#include "./warrior.h"
#include "./commander.h"
#include "./city.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_WOW_WAR_H
#define FINAL_WOW_WAR_H

// -------------------------------------------------------
// class definition
// -------------------------------------------------------

// -------------------------------------------------------
// Game class
// -------------------------------------------------------

class WorldOfWarcraft {
    // Production order of each commander.
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    // logging
    Logger l;

    // Game data field.
    size_t c = 0; // timestamp count in hours
    size_t n = 0; // Number of cities
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED, l ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE, l ); // blue headquarter
    City** C; // City list from 0 to N + 1

    static std::string getTimeStr( size_t c );

    /**
     * Has the next round?
     *
     * @param t Time period when we report the battlefield.
     * */

    bool hasNext( int t ) const;

    /**
     * Set up the game.
     *
     * @param n_ Number of cities excluding city 0 and N + 1.
     * */

    void setUp( size_t n_ );

    /**
     * Clean up after the game.
     * */

    void cleanUp();

    /**
     * XXX:05 - Lion whose loyalty <= 0 escapes.
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void lionEscaping( int t_, const char* t_str );

    /**
     * XXX:10 - move one step forward
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void moveForward( int t, const char* t_str );

    /**
     * XXX:35 - Wolf robbing action
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void wolfRobbing( int t, const char* t_str );

    /**
     * XXX:40 - battle starts
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void startBattle( int t, const char* t_str );

    /**
     * XXX:50 - headquarters report remained life points
     * and
     * XXX:55 - Warriors report their owned weapons.
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void report( int t, const char* t_str );

public:
    WorldOfWarcraft() : WorldOfWarcraft( WARNING ) {}

    WorldOfWarcraft( LogLevel ll ) : l( Logger( ll ) ) {
        // Initialize the city list
        C = new City*[ MAX_CITY_NUM + 2 ];
        for ( size_t i = 0; i < MAX_CITY_NUM + 2; i++ ) {
            if ( i == 0 ) C[ i ] = new City( i, &comm_red, l ); // city 0
            else if ( i == MAX_CITY_NUM + 1 ) C[ i ] = new City( i, &comm_blue, l ); // city N + 1
            else C[ i ] = new City( i, nullptr, l ); // cities in between
        }
    }

    ~WorldOfWarcraft() {
        for ( size_t i = 0; i < MAX_CITY_NUM + 2; i++ ) {
            delete C[ i ];
        }

        delete [] C;
    }

    /**
     * Start the game.
     *
     * @param m_ Total life points.
     * @param n_ Number of cities.
     * @param k_ Loyalty consumption points
     * @param t_ Time period when we report the battlefield.
     * @param M_ Array to indicate life points to generate a warrior.
     * @param P_ Array to indicate power points of a warrior.
     * */

    void start( size_t m_, size_t n_, size_t k_, int t_, const size_t* M_, const size_t* P_ );
};

// -------------------------------------------------------
// Helper functions
// -------------------------------------------------------

/**
 * Debugging setting.
 *
 * @return {
 *              { Input file stream, cin's original buffer },
 *              { Output file stream, cout's original buffer },
 *         }
 * */

std::pair<std::pair<
    std::ifstream*, std::basic_streambuf<char>*>,
    std::pair<std::ofstream*, std::basic_streambuf<char>*>
> debuggingSetting( size_t fileIdx, bool isRedirectCin, bool isRedirectCout );

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

/**
 * Entry function to start the game and test.
 *
 * @param isDebug To tell if to enable debugging model. Other parameters will be ignored if it's false.
 * @param fileIdx Test file index.
 * @param isRedirectCin To tell if to redirect input to the standard input.
 * @param isRedirectCout To tell if to redirect output to the standard output.
 * */

void caller( bool isDebug, size_t fileIdx, bool isRedirectCin, bool isRedirectCout );

#endif //FINAL_WOW_WAR_H
