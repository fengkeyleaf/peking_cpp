/*
 * simple_filter.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/simple_filter.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T, class F>
T *Filter( T *s, T *e, T *R, F *f ) {
    for ( ; s != e; s += 1 ) {
        if ( f( *s ) ) {
            *R = *s;
            R += 1;
        }
    }

    return R;
}

bool LargerThan2( int n ) {
    return n > 2;
}

bool LongerThan3( std::string s ) {
    return s.length() > 3;
}

void caller() {
    std::string as1[5] = { "Tom", "Mike", "Jack", "Ted", "Lucy" };
    std::string as2[5];
    int a1[5] = { 1, 2, 3, 4, 5 };
    int a2[5];
    std::string *p = Filter( as1, as1 + 5, as2, LongerThan3 );
    for ( int i = 0; i < p - as2; ++i )
        std::cout << as2[ i ]; // MikeJackLucy
    std::cout << std::endl;
    int *p2 = Filter( a1, a1 + 5, a2, LargerThan2 );
    for ( int i = 0; i < p2 - a2; ++i )
        std::cout << a2[ i ] << ","; // 3,4,5,
}