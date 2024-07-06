/*
 * my_ostream_iterator.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/6/2024
 */

#include "../include/my_ostream_iterator.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T1, class T2>
void Copy( T1 s, T1 e, T2 x ) {
    for ( ; s != e; ++s, ++x )
        *x = *s;
}

void caller() {
    const int SIZE = 5;
    int a[SIZE] = { 5, 21, 14, 2, 3 };
    double b[SIZE] = { 1.4, 5.56, 3.2, 98.3, 3.3 };
    std::list<int> lst( a, a + SIZE );
    myostream_iteraotr<int> output( std::cout, "," );
    Copy( lst.begin(), lst.end(), output );
    std::cout << std::endl;
    myostream_iteraotr<double> output2( std::cout, "--" );
    Copy( b, b + SIZE, output2 );
}

// https://en.cppreference.com/w/cpp/iterator/ostream_iterator
// https://en.cppreference.com/w/cpp/iterator/ostream_iterator/operator%3D
void sample() {
    std::ostream_iterator<int> i1( std::cout, ", " );
    *i1++ = 1; // usual form, used by standard algorithms
    *++i1 = 2;
    i1 = 3; // neither * nor ++ are necessary
    std::ostream_iterator<double> i2( std::cout );
    i2 = 3.14;
    std::cout << '\n';
}