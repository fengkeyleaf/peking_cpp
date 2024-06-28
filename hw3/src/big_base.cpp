/*
 * big_base.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/27/2024
 */

#include "../include/big_base.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void caller() {
    int n;
    while ( std::cin >> n ) {
        Big a1( n );
        Big a2 = a1;
        std::cout << a1.v << "," << a1.b.k << std::endl;
        std::cout << a2.v << "," << a2.b.k << std::endl;
    }
}
