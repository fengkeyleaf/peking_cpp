/*
 * what_to_return.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/27/2024
 */

#include <iostream>
#include <string>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW3_WHAT_TO_RETURN_H
#define HW3_WHAT_TO_RETURN_H

class Base {
public:
    int k;

    Base( int n ) : k( n ) {}
};

class Big {
public:
    int v;
    Base b;

    Big( int i ) : v( i ), b( i ) {}

    // Big( Big &g ) : v( g.v ), b( g.b ) {} // Unnecessary
};

void caller();

#endif //HW3_WHAT_TO_RETURN_H
