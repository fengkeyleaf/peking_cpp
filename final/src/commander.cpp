/*
 * commander.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "../include/commander.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// -------------------------------------------------------
// class Commander
// -------------------------------------------------------

// https://www.geeksforgeeks.org/cpp-printf-function/
const char* Commander::OUTPUT_FORMAT = "%s:00 %s %s %d born\n";

Warrior* Commander::getWarrior(
    Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_
) const {
    switch ( t_ ) {
        case dragon:
            return new Dragon( warrior_m_, p_, n_, m_, l );
        case ninja:
            return new Ninjia( warrior_m_, p_, n_, l );
        case iceman:
            return new Iceman( warrior_m_, p_, n_, l );
        case lion:
            return new Lion( warrior_m_, p_, n_, m_, k, l );
        case wolf:
            return new Wolf( warrior_m_, p_, n_, l );
        default:
            assert( false );
            return nullptr;
    }
}

int Commander::hasNext() {
    // Have to explicitly cast M[ W_n[ ( idx + 1 ) % WARRIOR_NUM ] ] to int,
    // otherwise the result will always be unsigned int, which is never less than 0.
    if ( m - ( int ) M[ W_n[ ( idx + 1 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 1 ) % WARRIOR_NUM;

    return -1;
}

void Commander::initResource( int m_, size_t k_, const size_t* M_, const size_t* P_ ) {
    m = m_;
    k = k_;
    M = M_;
    P = P_;
    n = 0;
    std::fill( std::begin( C ), std::end( C ), 0 );
    idx = -1;
    is_stopped = false;
    is_occupied = false;
}

Warrior* Commander::generate( const char* t ) {
    // Has been occupied, no actions.
    if ( is_occupied ) return nullptr;

    // Otherwise, try to generate a warrior.
    int idx_ = hasNext();
    // Doesn't have the ability to generate a warrior
    if ( idx_ < 0 ) { return nullptr; }

    // Only record the last warrior after it's generated.
    idx = idx_;
    // Yes, get the info of the warrior.
    int idx_global = W_n[ idx ]; // Global warrior enum idx.
    size_t warrior_m = M[ idx_global ];
    const char *color_name = COLOR_NAMES[ c ];
    const char *warrior_name = WARRIOR_NAMES[ idx_global ].c_str();

    // Reduce total life points.
    m -= warrior_m;
    // Output the production text.
    // "%s:00 %s %s %d born\n
    std::cout << stringFormat(
        OUTPUT_FORMAT,
        t, // timestamp
        color_name,
        warrior_name,
        ++n // Number
    );
    // Generate the warrior instance and return to the game coordinator.
    return getWarrior(
        static_cast<Warrior_enum>( idx_global ),
        warrior_m, P[ idx_global ], n, m
    );
}

void Commander::report( const char* t ) const {
    if ( is_occupied ) return;

    std::cout << stringFormat(
        "%s:50 %d elements in %s headquarter\n",
        t,
        m,
        COLOR_NAMES[ c ]
    );
}