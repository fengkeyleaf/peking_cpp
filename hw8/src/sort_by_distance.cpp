/*
 * sort_by_distance.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include "../include/sort_by_distance.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T1, class T2>
bool Closer<T1, T2>::operator()( const T1 &a_, const T1 &b_ ) {
    // Compare a_ and b_ with the base
    int r = f( a_, b ) - f( b_, b );
    return r == 0 ? a_ < b_ : r < 0;
}

int Distance1( int n1, int n2 ) {
    return std::abs( n1 - n2 );
}

int Distance2( const std::string &s1, const std::string &s2 ) {
    return std::abs( ( int ) s1.length() - ( int ) s2.length() );
}

void caller() {
    int a[10] = { 0, 3, 1, 4, 7, 9, 20, 8, 10, 15 };
    std::string b[6] = { "American", "Jack", "To", "Peking", "abcdefghijklmnop", "123456789" };

    int n;
    std::string s;
    while ( std::cin >> n >> s ) {
        std::sort(
            a, a + 10,
            Closer<int, int ( * )( int, int )>( n, Distance1 )
        );
        for ( int i = 0; i < 10; ++i )
            std::cout << a[ i ] << ",";
        std::cout << std::endl;
        std::sort(
            b, b + 6,
            Closer<std::string, int ( * )( const std::string &, const std::string & )>( s, Distance2 )
        );
        for ( int i = 0; i < 6; ++i )
            std::cout << b[ i ] << ",";
        std::cout << std::endl;
    }
}