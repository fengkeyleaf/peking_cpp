/*
 * mysterious_init_array.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include "../include/mysterious_init_array.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// https://stackoverflow.com/questions/8108416/excess-elements-of-scalar-initializer-for-pointer-to-array-of-ints
// https://www.geeksforgeeks.org/pointer-array-array-pointer/
void caller() {
    int *a[] = {
        nullptr,
        new int[ 6 ] { 1, 2, 3, 4, 5, 6 },
        new int[ 6 ] { 1, 2, 3, 4, 5, 6 },
        new int[ 6 ] { 1, 2, 3, 4, 5, 6 }
    };

    *a[ 2 ] = 123;
    a[ 3 ][ 5 ] = 456;
    if ( !a[ 0 ] ) {
        std::cout << *a[ 2 ] << "," << a[ 3 ][ 5 ]; // 123,456
    }
}