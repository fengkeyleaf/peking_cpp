/*
 * goodcopy.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include "../include/goodcopy.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T>
void GoodCopy<T>::operator()( T *s, T *e, T *D ) {
    int n = e - s; // How many elements we wanna copy
    assert( n >= 0 );

    if ( !n ) return; // Zero element to be copied.

    D += n - 1;
    e--;
    for ( ; s != e; e-- ) {
        *D = *e;
        D--;
    }

    *D = *e; // equivalent to *D = *s
}

template<class T>
void Print( T s, T e ) {
    for ( ; s != e; ++s )
        std::cout << *s << ",";
    std::cout << std::endl;
}

void caller() {
    int a[200];
    int b[200];
    std::string c[200];
    std::string d[200];

    int t;
    std::cin >> t;
    while ( t-- ) {
        int m;
        std::cin >> m;
        for ( int i = 0; i < m; ++i )
            std::cin >> a[ i ];
        GoodCopy<int>()( a, a + m, b );
        Print( b, b + m );
        GoodCopy<int>()( a, a + m, a + m / 2 );
        Print( a + m / 2, a + m / 2 + m );

        for ( int i = 0; i < m; ++i )
            std::cin >> c[ i ];
        GoodCopy<std::string>()( c, c + m, d );
        Print( c, c + m );
        GoodCopy<std::string>()( c, c + m, c + m / 2 );
        Print( c + m / 2, c + m / 2 + m );
    }
}