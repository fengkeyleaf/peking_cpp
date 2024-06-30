/*
 * simplify_big_int.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/30/2024
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW4_SIMPLIFY_BIG_INT_H
#define HW4_SIMPLIFY_BIG_INT_H

#define MAX_SIZE 211
#define MAX_INPUT_SIZE 200

class CHugeInt {
    char *C;
    int v;
    bool is_big;
public:
    CHugeInt( int n ) {
        is_big = false;
        v = n;

        std::string n_str = std::to_string( n );
        C = new char[ n_str.size() ];
        char const *s = n_str.c_str();
        std::copy( s, s + n_str.length(), C );
    }

    CHugeInt( const char *S ) {
        is_big = true;
        v = -1;
        C = new char[ MAX_INPUT_SIZE ];
        std::copy( S, S + MAX_INPUT_SIZE, C );
    }

    ~CHugeInt() {
        delete [] C;
    }

    CHugeInt &operator+( const CHugeInt &i );

    friend CHugeInt &operator+( int n, const CHugeInt &i );

    friend std::ostream &operator<<( std::ostream &os, const CHugeInt &i );

    CHugeInt &operator+=( int n );

    // https://learn.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170
    CHugeInt &operator++();

    CHugeInt &operator++( int n );
};

void caller();

#endif //HW4_SIMPLIFY_BIG_INT_H
