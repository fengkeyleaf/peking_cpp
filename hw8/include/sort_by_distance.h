/*
 * sort_by_distance.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW8_SORT_BY_DISTANCE_H
#define HW8_SORT_BY_DISTANCE_H

// https://en.cppreference.com/w/cpp/algorithm/sort
template<class T1, class T2>
struct Closer {
    T1 &b; // base
    T2 f; // functor

public:
    Closer( T1 &b_, T2 f_ ) : b( b_ ), f( f_ ) {}

    bool operator()( const T1 &a_, const T1 &b_ );
};

int Distance1( int n1, int n2 );

int Distance2( const std::string &s1, const std::string &s2 );

void caller();

#endif //HW8_SORT_BY_DISTANCE_H
