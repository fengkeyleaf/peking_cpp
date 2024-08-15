/*
 * commander.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "./config.h"
#include "./warrior.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_COMMANDER_H
#define FINAL_COMMANDER_H

class Commander {
    const static char* OUTPUT_FORMAT;

    int m; // total life points
    size_t k; // loyalty consumption points.
    const int* W_n; // local warrior names
    const size_t* M; // Warrior life points
    const size_t* P; // Warrior power points
    size_t n = 0; // warrior total count
    size_t C[ WARRIOR_NUM ] = { 0 }; // warrior count
    int idx = -1; // Warrior index. i.e. which warrior generated in last round.
    bool is_stopped = false; // Is stopping generating warriors? i.e. normal termination without occupation
    bool is_occupied = false;
    // logging
    Logger& l;

    /**
     * Generate a warrior, but only print out its info for this assignment.
     *
     * @param t_ Warrior enum type.
     * @param warrior_m_ Warrior life point.
     * @param p_ Warrior power point.
     * @param n_ Warrior number id.
     * @param m_ Remained life points of the commander.
     * */

    Warrior* getWarrior( Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_ ) const;

public:
    const Color_enum c; // color

    Commander( Color_enum c, const int *W, Logger& l_ ) : c( c ), W_n( W ), l( l_ ) {}

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

    Warrior* generate( const char* t );

    /**
     * Initialize resources.
     *
     * @param m_ Total life points.
     * @param k_ Loyalty consumption points
     * @param M_ Array to indicate life points to generate a warrior.
     * @param P_ Array to indicate power points of a warrior.
     * */

    void initResource( int m_, size_t k_, const size_t* M_, const size_t* P_ );

    void report( const char* t ) const;

    // -------------------------------------------------------
    // Setter and getter
    // -------------------------------------------------------

    void setOccupied() { is_occupied = true; }

    bool IsOccupied() const { return is_occupied; }
};

#endif //FINAL_COMMANDER_H
