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

// http://cxsjsxmooc.openjudge.cn/2023t3spring/045/
/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

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

bool WorldOfWarcraft::hasTime( int t ) const {
    // This conditional statement also includes the situation
    // where the t == 0, i.e. the game finishes as soon as each commander generates a warrior.
    return t - ( int ) c * 60 >= 0;
}

void WorldOfWarcraft::setUp( size_t n_ ) {
    c = 0; // Time starting at 000:00
    n = n_; // Number of cities excluding 0 and N + 1
    // Set id for the city N + 1.
    C[ MAX_CITY_NUM + 1 ]->setId( n + 1 );
    // Move city N + 1 to the last one which is n + 1
    std::swap( C[ n + 1 ], C[ MAX_CITY_NUM + 1 ] );
}

void WorldOfWarcraft::cleanUp() {
    // Clean up resources for each city.
    for ( size_t i = 0; i < n + 2; i++ ) {
        assert( i != 0 or i != n - 1 or C[ i ]->getCommander() != nullptr );
        C[ i ]->cleanUp();
    }
    // Move city N + 1 to the last one which is N + 1.
    std::swap( C[ n + 1 ], C[ MAX_CITY_NUM + 1 ] );
    // Set id for the city N + 1.
    C[ MAX_CITY_NUM + 1 ]->setId( MAX_CITY_NUM + 1 );
}

void WorldOfWarcraft::lionEscaping( int t_, const char* t_str ) {
    if ( t_ < 0 ) return;

    // Lion-escaping may happen in city 0 and city N + 1
    // when a lion with loyalty <= 0 in the beginning.
    for ( size_t i = 0; i < n + 2; i++ ) {
        C[ i ]->lionEscaping( t_str );
    }
}

void WorldOfWarcraft::moveForward( int t, const char* t_str ) {
    if ( t < 0 ) return;

    // Events happening at the same time, report them from east to west,
    // so move blue warriors first, then red warriors.
    // Don't forget city 0 and N + 1.
    for ( size_t i = 0; i < n + 1; i++ ) {
        // Start from east to west.
        // i.e. move a blue warrior at city i to i - 1.
        C[ i + 1 ]->moveForwardBlue( C[ i ], t_str );
    }

    for ( int i = n + 1; i > 0; i-- ) {
        // Start from west to east.
        // i.e. move a red warrior at city i to i + 1
        C[ i - 1 ]->moveForwardRed( C[ i ], t_str );
    }
}

void WorldOfWarcraft::wolfRobbing( int t, const char* t_str ) {
    if ( t < 0 ) return;

    for ( size_t i = 1; i < n + 1; i++ ) {
        C[ i ]->wolfRobbing( t_str );
    }
}

void WorldOfWarcraft::startBattle( int t, const char* t_str ) {
    if ( t < 0 ) return;

    for ( size_t i = 1; i < n + 1; i++ ) {
        C[ i ]->startBattle( t_str );
    }
}

void WorldOfWarcraft::report( int t, const char* t_str ) {
    // XXX:50 - headquarters report remained life points
    if ( t - 50 >= 0 ) {
        comm_red.report( t_str );
        comm_blue.report( t_str );
    }

    // XXX:55 - Warriors report their owned weapons.
    if ( t - 55 >= 0 ) {
        // Warriors arriving the headquarters don't report.
        for ( size_t i = 1; i < n + 1; i++ ) {
            C[ i ]->report( t_str );
        }
    }
}

void WorldOfWarcraft::start(
    size_t m_, size_t n_, size_t k_, int t_,
    const size_t* M_, const size_t* P_
) {
    // Wow game resource initialization
    setUp( n_ );
    // Commander initialization.
    comm_red.initResource( m_, k_, M_, P_ );
    comm_blue.initResource( m_, k_, M_, P_ );

    // Start the game.
    const char* s = nullptr;
    while ( hasTime( t_ ) ) {
        // https://en.cppreference.com/w/cpp/string/basic_string/c_str
        std::string t_str = getTimeStr( c ); // Avoid the string to be destroyed.
        s = t_str.c_str();

        // XXX:00 - generate a warrior by consuming life points.
        // Each headquarter generates a warrior if possible.
        // and report the warriors it generates.
        Warrior* w_red = comm_red.generate( s );
        if ( w_red ) { l.debug( w_red->print().c_str() ); }
        Warrior* w_blue = comm_blue.generate( s );
        if ( w_blue ) { l.debug( w_blue->print().c_str() ); }

        // Add warriors to the two cities, city 0 and n + 1.
        C[ 0 ]->addWarrior( w_red );
        C[ n + 1 ]->addWarrior( w_blue );

        // Time remained with respect to hours.
        int t_remained = t_ - c * 60;
        // XXX:05 - Lion whose loyalty <= 0 escapes.
        lionEscaping( t_remained - 5, s );
        // XXX:10 - move one step forward
        moveForward( t_remained - 10, s );
        // XXX:35 - Wolf robbing action;
        wolfRobbing( t_remained - 35, s );
        // XXX:40 - battle starts
        startBattle( t_remained - 40, s );
        // Reporting events.
        report( t_remained, s );

        // Increment the timestamp by one hour.
        c++;
    }

    // Don't need code to handle additional time,
    // since we start time counting from 0. e.g.
    // if t = 60, 60 - 0 * 60 = 60 >= 0.
    // would go through all events in that 60 mins,
    // Similarly, t = 80, 80 - 0 * 60 = 80 >= 0,
    // handle events in the first hour/60 mins,
    // and 80 - 1 * 60 = 20 >= 0,
    // handle events in the remained 20 mins.
    cleanUp();
}

// -------------------------------------------------------
// Helper functions
// -------------------------------------------------------

std::pair<std::ifstream*, std::ofstream*> debuggingSetting(
    bool isDebug, size_t fileIdx, bool isRedirectCout )
{
    if ( !isDebug ) return std::pair<std::ifstream*, std::ofstream*>( nullptr, nullptr );

    const size_t N = 4;
    const char* TEST_PATHS[ N ] = {
        "/home/sora/perking_cpp/final/tests/in_war_1", // Example test case on the website.
        "/home/sora/perking_cpp/final/tests/in_war_2", // 3.1) Not enough life points to generate any warriors.
        "/home/sora/perking_cpp/final/tests/in_war_3", // 3.4) t = 0
        "/home/sora/perking_cpp/final/tests/in_war_4", // Test_1
    };
    assert( fileIdx < 4 );

    // Debugging setting
    std::ifstream* fi = new std::ifstream( TEST_PATHS[ fileIdx ] );
    std::cin.rdbuf( fi->rdbuf() );
    std::ofstream* fo = new std::ofstream(
        "/home/sora/perking_cpp/final/tests/out_war_" + std::to_string( fileIdx + 1 )
    );
    if ( isRedirectCout ) std::cout.rdbuf( fo->rdbuf() );

    return std::pair<std::ifstream*, std::ofstream*>( fi, fo );
}

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller( bool isDebug, size_t file_idx, bool isRedirectCout ) {
    auto p = debuggingSetting( isDebug, file_idx, isRedirectCout );

    size_t c; // Number of test cases.
    size_t m; // Total life points.
    size_t n; // Number of cities.
    size_t k; // Loyalty consumption points
    size_t t; // Time
    size_t M[ WARRIOR_NUM ]; // Life points.
    size_t P[ WARRIOR_NUM ]; // Power points.
    WorldOfWarcraft wow = WorldOfWarcraft( isDebug ? DEBUG : INFO ); // Game coordinator

    std::cin >> c;
    for ( int i = 1; i <= c; i++ ) {
        std::cout << "Case:" << i << std::endl;

        std::cin >> m;
        assert( 1 <= m && m <= 100000 );
        std::cin >> n;
        assert( 1 <= n && n <= 20 );
        std::cin >> k;
        assert( 0 <= k && k <= 100 );
        std::cin >> t;
        assert( 0 <= t && t <= 6000 );

        for ( size_t &j : M ) {
            std::cin >> j;
            assert( 0 < j && j <= 200 );
        }

        for ( size_t &j : P ) {
            std::cin >> j;
            assert( 0 < j && j <= 200 );
        }

        wow.start( m, n, k, t, M, P );
    }

    if ( isDebug ) {
        p.first->close();
        delete p.first;
        p.second->close();
        delete p.second;
    }
}

