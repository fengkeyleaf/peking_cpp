/*
 * my_set.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/7/2024
 */

#include "../include/my_set.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void MySet::add( int x ) {
    if ( M.find( x ) == M.end() ) M[ x ] = 0; // add a container for x;

    std::cout << ++M[ x ] << std::endl;
}

void MySet::del( int x ) {
    if ( M.find( x ) == M.end() ) {
        std::cout << 0 << std::endl;
        return;
    }

    size_t n = M[ x ];
    M[ x ] = 0;
    std::cout << n << std::endl;
}

void MySet::ask( int x ) {
    if ( M.find( x ) == M.end() ) {
        std::cout << 0 << " " << 0 << std::endl;
        return;
    }

    std::cout << 1 << " " << M[ x ] << std::endl;
}

void caller() {
    MySet S;

    int n;
    std::cin >> n;
    while ( n-- ) {
        int x;
        std::string s;
        std::cin >> s;
        if ( s == "add" ) {
            std::cin >> x;
            S.add( x );
        }
        else if ( s == "del" ) {
            std::cin >> x;
            S.del( x );
        }
        else if ( s == "ask" ) {
            std::cin >> x;
            S.ask( x );
        }
    }
}

