/*
 * coolblood_arena.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/7/2024
 */

#include "../include/coldblood_arena.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void caller() {
    Game g;

    // Debugging setting
    std::ifstream fi( "/home/sora/perking_cpp/hw9/in_coldblood.txt" );
    std::cin.rdbuf( fi.rdbuf() );
    g.redirect_to_file();

    int n;
    std::cin >> n;
    while( n-- ) {
        size_t id, p;
        std::cin >> id >> p;
        g.add( id, p );
    }

    fi.close();
}