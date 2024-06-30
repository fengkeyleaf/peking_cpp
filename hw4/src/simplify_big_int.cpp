/*
 * simplify_big_int.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/30/2024
 */

#include "../include/simplify_big_int.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

const int MAX = 110;

void caller() {
    char s[ 210 ]; // max: 200
    int n; // 0 ~ 2,147,483,647

    while ( std::cin >> s >> n ) {
        CHugeInt a( s );
        CHugeInt b( n );

        std::cout << a + b << std::endl;
        std::cout << n + a << std::endl;
        std::cout << a + n << std::endl;
        b += n;
        std::cout << ++b << std::endl;
        std::cout << b++ << std::endl;
        std::cout << b << std::endl;
    }
}