/*
 * wow_weapons.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/8/2024
 */

#include "../include/wow_weapons.h"

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
// Weapon class
// -------------------------------------------------------

Weapon_enum Weapon::get_type() const {
    return t;
}

// -------------------------------------------------------
// Warrior class
// -------------------------------------------------------

Weapon *Warrior::get_weapon( Weapon_enum t_, size_t p_ ) {
    switch ( t_ ) {
        case sword:
            return new Sword( p_ );
        case bomb:
            return new Bomb( p_ );
        case arrow:
            return new Arrow( p_ );
        default:
            assert( false );
            return nullptr;
    }
}

const char* Dragon::OUT_FORMAT = "It has a %s,and it's morale is %.2f\n";
inline void Dragon::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ],
        morale
    );
}

const char* Ninjia::OUT_FORMAT = "It has a %s and a %s\n";
inline void Ninjia::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ],
        WEAPON_NAMES[ W_init[ 1 ]->get_type() ]
    );
}

const char* Iceman::OUT_FORMAT = "It has a %s\n";
inline void Iceman::print() {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ]
    );
}

const char* Lion::OUT_FORMAT = "It's loyalty is %ld\n";
inline void Lion::print() {
    printf(
        OUT_FORMAT,
        loyalty
    );
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

void WorldOfWarcraft::start( size_t n, size_t m, const size_t *M  ) {
    std::cout << "Case:" << n << std::endl;

    c = 0;
    comm_red.initResource( m, M );
    comm_blue.initResource( m, M );

    std::string s;
    while ( comm_red.hasNext() >= 0 || comm_blue.hasNext() >= 0 ) {
        s = getTimeStr( c );
        comm_red.generate( s );
        comm_blue.generate( s );
        c++;
    }

    s = getTimeStr( c );
    comm_red.generate( s );
    comm_blue.generate( s );
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

Warrior* Commander::get_warrior(
    size_t id_, Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_
) {
    switch ( t_ ) {
        case dragon:
            return new Dragon( id_, warrior_m_, p_,  n_, m_ );
        case ninja:
            return new Ninjia( id_, warrior_m_, p_, n_ );
        case iceman:
            return new Iceman( id_, warrior_m_, p_, n_ );
        case lion:
            return new Lion( id_, warrior_m_, p_, m_ );
        case wolf:
            return new Wolf( id_, warrior_m_, p_ );
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

void Commander::initResource( int m, const size_t *M ) {
    this->m = m;
    this->M = M;
    n = 0;
    std::fill( std::begin( C ), std::end( C ), 0 );
    idx = -1;
    is_stopped = false;
}

void Commander::generate( std::string &t ) {
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

        return;
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
    Warrior* w = get_warrior(
        n, static_cast<Warrior_enum>( idx_global ), warrior_m, 0, n, m
    );
    w->print();
    delete w;
}

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller() {
    int n, m;
    size_t M[ WARRIOR_NUM ];
    WorldOfWarcraft wow = WorldOfWarcraft();

    std::cin >> n;
    for ( int i = 1; i <= n; i++ ) {
        std::cin >> m;

        for ( size_t &j : M ) {
            std::cin >> j;
        }

        wow.start( i, m, M );
    }
}
