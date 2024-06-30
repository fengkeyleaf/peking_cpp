/*
 * twoD_array.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include "../include/twoD_array.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void caller() {
    Array2 a( 3, 4 );
    int i, j;
    for ( i = 0; i < 3; ++i )
        for ( j = 0; j < 4; j++ )
            a[ i ][ j ] = i * 4 + j;
    for ( i = 0; i < 3; ++i ) {
        for ( j = 0; j < 4; j++ ) {
            std::cout << a( i, j ) << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "next" << std::endl;
    Array2 b;
    b = a;
    for ( i = 0; i < 3; ++i ) {
        for ( j = 0; j < 4; j++ ) {
            std::cout << b[ i ][ j ] << ",";
        }
        std::cout << std::endl;
    }
}