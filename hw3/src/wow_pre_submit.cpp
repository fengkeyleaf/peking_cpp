/*
 * wow_pre_submit.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/28/2024
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

#define WARRIOR_NUM 5

enum Color {
    red,
    blue
};

const char *COLOR_NAMES[] = {
    "red",
    "blue"
};

enum Warrior {
    dragon, // = 0
    ninja, // = 1
    iceman, // = 2
    lion, // = 3
    wolf // = 4
};

// -------------------------------------------------------
// class Commander
// -------------------------------------------------------

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
    int hasNext();
    void generate( std::string &t );
    void initResource( int m, const unsigned *M );
};

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

int Commander::hasNext() {
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

void Commander::initResource( int m, const unsigned int *M ) {
    this->m = m;
    this->M = M;
    n = 0;
    std::fill( std::begin( C ), std::end( C ), 0 );
    idx = -1;
    is_stopped = false;
}

void Commander::generate( std::string &t ) {
    idx = hasNext();
    if ( idx < 0 ) {
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

    int idx_global = W_n[ idx ];
    unsigned int warrior_m = M[ idx_global ];
    const char *color_name = COLOR_NAMES[ c ];
    const char *warrior_name = WARRIOR_NAMES[ idx_global ].c_str();

    m -= warrior_m;
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
}

// -------------------------------------------------------
// class WorldOfWarcraft
// -------------------------------------------------------

class WorldOfWarcraft {
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    unsigned int c = 0; // timestamp
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE ); // blue headquarter

    static std::string getTimeStr( unsigned int c );

public:
    void start( unsigned int n, unsigned int m, const unsigned int *M );
};

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

void WorldOfWarcraft::start( unsigned int n, unsigned int m, const unsigned int *M  ) {
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
std::string WorldOfWarcraft::getTimeStr( unsigned int c ) {
    std::string s = std::to_string( c );
    assert( s.size() < 4 );

    switch ( s.size() ) {
        case 1:
            s.insert( 0, 2, '0' );
            break;
        case 2:
            s.insert( 0, 1, '0' );
            break;
    }

    return s;
}

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller() {
    int n, m;
    unsigned int M[ WARRIOR_NUM ];
    WorldOfWarcraft wow = WorldOfWarcraft();

    std::cin >> n;
    for ( int i = 1; i <= n; i++ ) {
        std::cin >> m;

        for ( unsigned int &j : M ) {
            std::cin >> j;
        }

        wow.start( i, m, M );
    }
}

int main() {
    caller();

    return 0;
}
