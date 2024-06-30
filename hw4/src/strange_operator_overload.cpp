/*
 * strange_operator_overload.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include "../include/strange_operator_overload.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

int Inc( int n ) {
    return n + 1;
}

void caller() {
    int n;
    while ( std::cin >> n ) {
        MyInt objInt( n );
        objInt - 2 - 1 - 3;
        std::cout << Inc( objInt );
        std::cout << ",";
        objInt - 2 - 1;
        std::cout << Inc( objInt ) << std::endl;
    }
}