/*
 * strange_return.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include "../include/strange_return.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

int &getElement( int *a, int i ) {
    return a[ i ];
}

void caller() {
    int a[] = { 1, 2, 3 };
    getElement( a, 1 ) = 10;
    std::cout << a[ 1 ];
}