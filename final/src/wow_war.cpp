/*
 * wow_war.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/10/2024
 */

#include "../include/wow_war.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// https://stackoverflow.com/questions/17764661/multiple-definition-of-linker-error
const char *COLOR_NAMES[] = {
    "red",
    "blue"
};

const char *WEAPON_NAMES[] = {
    "sword",
    "bomb",
    "arrow"
};

// -------------------------------------------------------
// Warrior class
// -------------------------------------------------------

const char* Dragon::OUT_FORMAT = "It has a %s,and it's morale is %.2f\n";
inline void Dragon::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_ids[ 0 ] ],
        morale
    );
}

const char* Ninjia::OUT_FORMAT = "It has a %s and a %s\n";
inline void Ninjia::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_ids[ 0 ] ],
        WEAPON_NAMES[ W_ids[ 1 ] ]
    );
}

const char* Iceman::OUT_FORMAT = "It has a %s\n";
inline void Iceman::print() {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_ids[ 0 ] ]
    );
}

const char* Lion::OUT_FORMAT = "It's loyalty is %ld\n";
inline void Lion::print() {
    printf(
        OUT_FORMAT,
        loyalty
    );
}

// TODO: Delete escaped lion.
bool Lion::escape( const char* t, const char* c ) {
    if ( loyalty <= 0 ) {
        printf(
            "%s:05 %s lion %ld ran away",
            t,
            c,
            id
        );
        return true;
    }

    loyalty -= k;
    return false;
}

// -------------------------------------------------------
// class City
// -------------------------------------------------------

void City::lionEscaping() {
    if ( r ) r->escape();
    if ( b ) b->escape();
}

void City::moveForward() {
    if ( r ) r->move();
    if ( b ) b->move();
}

void City::wolfRobbing() {
    if ( r ) r->rob();
    if ( b ) b->rob();
}

void City::startBattle() {
    if ( !r || !b ) return;

    bool attacking_order = isOdd;
    do {
        if ( attacking_order ) {
            r->attack( b );
            b->attack( r );
        }
        else {
            b->attack( r );
            r->attack( b );
        }

        attacking_order = !attacking_order;
    } while( r->isAttack() || b->isAttack() );

    // TODO: delete a warrior if necessary.
}

// -------------------------------------------------------
// class WorldOfWarcraft
// -------------------------------------------------------

const int WorldOfWarcraft::WARRIOR_NAMES_RED[ WARRIOR_NUM ] = {
    iceman,
    lion,
    wolf,
    ninja,
    dragon
};

const int WorldOfWarcraft::WARRIOR_NAMES_BLUE[ WARRIOR_NUM ] = {
    lion,
    dragon,
    ninja,
    iceman,
    wolf
};

inline bool WorldOfWarcraft::hasTime( size_t t ) {
    return ( int ) t - c * 60 >= 0;
}

void WorldOfWarcraft::lionEscaping( int t ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->lionEscaping();
    }
}

void WorldOfWarcraft::moveForward( int t, Warrior* r, Warrior* b ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->moveForward();
    }
}

void WorldOfWarcraft::wolfRobbing( int t ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->wolfRobbing();
    }
}

void WorldOfWarcraft::startBattle( int t ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->startBattle();
    }
}

void WorldOfWarcraft::report( int t ) {
    if ( t - 50 >= 0 ) {
        comm_red.report();
        comm_blue.report();
    }

    if ( t - 55 >= 0 ) {
        // TODO: report warrior.
    }
}

void WorldOfWarcraft::start(
    size_t m_, size_t n_, size_t k_, size_t t_, const size_t* M_, const size_t* P_
) {
    // Resource initialization
    c = 0;
    n = n_;
    C = new City* [ n ];
    for ( size_t i = 0; i < n; i++ ) {
        C[ i ] = new City( i % 2 != 0 );
    }
    comm_red.initResource( m_, k_, M_, P_ );
    comm_blue.initResource( m_, k_, M_, P_ );

    // Start battle.
    std::string s;
    while ( hasTime( t_ ) ) {
        s = getTimeStr( c );

        Warrior* w_red = comm_red.generate( s );
        Warrior* w_blue = comm_blue.generate( s );

        if ( w_red ) w_red->print();
        if ( w_blue ) w_blue->print();

        int t_remained = ( int ) t_ - c * 60;
        lionEscaping( t_remained - 5 );
        moveForward( t_remained - 10, w_red, w_blue );
        wolfRobbing( t_remained - 35 );
        startBattle( t_remained - 40 );
        report( t_remained );

        c++;
    }

    // TODO: need code?
}

// https://www.geeksforgeeks.org/how-to-add-leading-zeros-to-a-cpp-string/
std::string WorldOfWarcraft::getTimeStr( size_t c ) {
    std::string s = std::to_string( c );
    assert( s.size() < 4 );

    switch ( s.size() ) {
        // e.g. 1 => 001
        case 1:
            s.insert( 0, 2, '0' );
            break;
            // e.g. 22 => 022
        case 2:
            s.insert( 0, 1, '0' );
            break;
    }

    return s;
}

// -------------------------------------------------------
// class Commander
// -------------------------------------------------------

// https://brainly.com/question/49412407
const std::string Commander::WARRIOR_NAMES[ WARRIOR_NUM ] = {
    "dragon",
    "ninja",
    "iceman",
    "lion",
    "wolf"
};

// https://www.geeksforgeeks.org/cpp-printf-function/
const char* Commander::OUTPUT_FORMAT = "%s %s %s %d born with strength %d,%d %s in %s headquarter\n";

Warrior* Commander::get_warrior( Warrior_enum t_, size_t warrior_m_, size_t n_, int m_ ) {
    switch ( t_ ) {
        case dragon:
            return new Dragon( warrior_m_, n_, m_ );
        case ninja:
            return new Ninjia( warrior_m_, n_ );
        case iceman:
            return new Iceman( warrior_m_, n_ );
        case lion:
            return new Lion(  warrior_m_, m_, k );
        case wolf:
            return new Wolf( warrior_m_ );
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
    else if ( m - ( int ) M[ W_n[ ( idx + 2 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 2 ) % WARRIOR_NUM;
    else if ( m - ( int ) M[ W_n[ ( idx + 3 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 3 ) % WARRIOR_NUM;
    else if ( m - ( int ) M[ W_n[ ( idx + 4 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 4 ) % WARRIOR_NUM;
    else if ( m - ( int ) M[ W_n[ ( idx + 5 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 5 ) % WARRIOR_NUM;

    return -1;
}

void Commander::initResource( int m, size_t k, const size_t *M, const size_t *P ) {
    this->m = m;
    this->k = k;
    this->M = M;
    this->P = P;
    n = 0;
    std::fill( std::begin( C ), std::end( C ), 0 );
    idx = -1;
    is_stopped = false;
}

Warrior* Commander::generate( std::string &t ) {
    idx = hasNext();
    // Has the ability to generate a warrior?
    if ( idx < 0 ) {
        // No, output terminating text if necessary.
        if ( !is_stopped ) {
            is_stopped = !is_stopped;
            printf(
                "%s %s headquarter stops making warriors\n",
                t.c_str(),
                COLOR_NAMES[ c ]
            );
        }

        return nullptr;
    }

    // Yes, get the info of the warrior.
    int idx_global = W_n[ idx ];
    size_t warrior_m = M[ idx_global ];
    const char *color_name = COLOR_NAMES[ c ];
    const char *warrior_name = WARRIOR_NAMES[ idx_global ].c_str();

    // Reduce total life points.
    m -= warrior_m;
    // Output the production text.
    // https://stackoverflow.com/questions/10865957/how-to-use-printf-with-stdstring
    printf(
        OUTPUT_FORMAT,
        t.c_str(), // timestamp
        color_name,
        warrior_name,
        ++n, // Number
        warrior_m, // life/strength point
        ++C[ idx ], // Warrior count
        warrior_name,
        color_name
    );
    // Output the text for the warrior
    return get_warrior( static_cast<Warrior_enum>( idx_global ), warrior_m, n, m );
}

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller() {
    size_t c; // Number of test cases.
    size_t m; // Total life points.
    size_t n; // Number of cities.
    size_t k; // Loyalty consumption points
    size_t t; // Time
    size_t M[ WARRIOR_NUM ]; // Life points.
    size_t P[ WARRIOR_NUM ]; // Power points.
    WorldOfWarcraft wow = WorldOfWarcraft();

    std::cin >> c;
    for ( int i = 1; i <= c; i++ ) {
        std::cout << "Case:" << i << std::endl;

        std::cin >> m;
        std::cin >> n;
        std::cin >> k;
        std::cin >> t;

        for ( size_t &j : M ) {
            std::cin >> j;
        }

        for ( size_t &j : P ) {
            std::cin >> j;
        }

        wow.start( m, n, k, t, M, P );
    }
}
