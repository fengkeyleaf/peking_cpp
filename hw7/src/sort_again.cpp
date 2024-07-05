/*
 * sort_again.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include "../include/sort_again.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

bool Greater2( int n1, int n2 ) {
    return n1 > n2;
}

bool Greater1( int n1, int n2 ) {
    return n1 < n2;
}

bool Greater3( double d1, double d2 ) {
    return d1 < d2;
}

template<class T1, class T2>
void mysort( T1 *s, T1 *e, T2 *f ) {
    // swap sort
    for ( ; s != e; s += 1 ) {
        T1 *t = s + 1;
        for ( ; t != e; t += 1 ) {
            if ( !f( *s, *t ) ) {
                T1 tv = *s;
                *s = *t;
                *t = tv;
            }
        }
    }
}

void caller() {
    int an[ NUM ] = { 8, 123, 11, 10, 4 };
    mysort( an, an + NUM, Greater1 ); //从小到大排序 
    for ( int i = 0; i < NUM; i++ )
        std::cout << an[ i ] << ",";
    mysort( an, an + NUM, Greater2 ); //从大到小排序 
    std::cout << std::endl;
    for ( int i = 0; i < NUM; i++ )
        std::cout << an[ i ] << ",";
    std::cout << std::endl;
    double d[6] = { 1.4, 1.8, 3.2, 1.2, 3.1, 2.1 };
    mysort( d + 1, d + 5, Greater3 ); //将数组从下标1到下标4从小到大排序 
    for ( int i = 0; i < 6; i++ )
        std::cout << d[ i ] << ",";
}