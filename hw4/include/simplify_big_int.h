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
// https://learn.microsoft.com/en-us/cpp/cpp/assertion-and-user-supplied-messages-cpp?view=msvc-170
#include <cassert>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW4_SIMPLIFY_BIG_INT_H
#define HW4_SIMPLIFY_BIG_INT_H

#define MAX_INPUT_SIZE 201

// https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading
class CHugeInt {
    // https://www.asciitable.com/
    const static char UNITS_CARRY_IN[ 10 ];
    const static char UNITS[ 10 ];
    char *C;
    size_t s;

    CHugeInt add( const CHugeInt &i ) const;
    static void add_( const CHugeInt &max, const CHugeInt &min, char *C, size_t n );
    void copy( const CHugeInt &i );

public:
    CHugeInt(): C( nullptr ), s( 0 ) {}

    CHugeInt( int n ) {
        std::string n_str = std::to_string( n );
        s = n_str.size();
        C = new char[ s ];
        char const *n_char = n_str.c_str();
        std::copy( n_char, n_char + s, C );
    }

    CHugeInt( const char *S, size_t n ) {
        s = n;
        C = new char[ s ];
        std::copy( S, S + s, C );
    }

    CHugeInt( const char *S ) {
        s = 0;
        for ( int i = 0; i < MAX_INPUT_SIZE; i++ ) {
            // trail '\0'
            if ( S[ i ] == '\0' ) break;
            s++;
        }

        C = new char[ s ];
        std::copy( S, S + s, C );
    }

    CHugeInt( const CHugeInt& i ) {
        C = nullptr;
        s = 0;

        if ( !i.C ) { return; }

        copy( i );
    }

    ~CHugeInt() {
        delete [] C;
    }

    // --------------------------------------------------
    // Operator overloading
    // --------------------------------------------------

    friend CHugeInt operator+( const CHugeInt &a, const CHugeInt &b );

    friend CHugeInt operator+( int n, const CHugeInt &i );

    friend std::ostream &operator<<( std::ostream &os, const CHugeInt &i );

    CHugeInt &operator+=( int n );

    // https://learn.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170
    CHugeInt &operator++();

    CHugeInt operator++( int n );
};

void getMaxInput( char *s, size_t n );
void caller();

#endif //HW4_SIMPLIFY_BIG_INT_H
