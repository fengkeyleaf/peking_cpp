/*
 * while_cin.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/while_cin.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

MyCin &MyCin::operator>>( int &n ) {
    if ( !f ) return *this;

    std::cin >> n; // Always enter this line.
    if ( n == -1 ) f = false;

    return *this;
}

MyCin::operator bool() const {
    return f;
}

void caller() {
    MyCin m;
    int n1, n2;
    while ( m >> n1 >> n2 )
        std::cout << n1 << " " << n2 << std::endl;
}


