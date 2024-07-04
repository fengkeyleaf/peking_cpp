/*
 * simple_foreach.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/simple_foreach.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T, class F>
void MyForeach( T *s, T *e, F *f ) {
    for ( ; s != e; s += 1 ) {
        f( *s );
    }
}

void Print( std::string s ) {
    std::cout << s;
}

void Inc( int &n ) {
    ++n;
}

void caller() {
    std::string array[ 100 ];
    int a[ 100 ];

    int m, n;
    while ( std::cin >> m >> n ) {
        for ( int i = 0; i < m; ++i )
            std::cin >> array[ i ];
        for ( int j = 0; j < n; ++j )
            std::cin >> a[ j ];
        MyForeach( array, array + m, Print );
        std::cout << std::endl;
        MyForeach( a, a + n, Inc );
        for ( int i = 0; i < n; ++i )
            std::cout << a[ i ] << ",";
        std::cout << std::endl;
    }
}