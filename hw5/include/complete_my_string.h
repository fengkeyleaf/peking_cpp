/*
 * complete_my_string.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/2/2024
 */

#include <cstdlib>
#include <iostream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW5_COMPLETE_MY_STRING_H
#define HW5_COMPLETE_MY_STRING_H

int strlen( const char *s );

void strcpy( char *d, const char *s );

int strcmp( const char *s1, const char *s2 );

void strcat( char *d, const char *s );

// TODO: Follow-up 1): Deal with "", i.e. C = nullptr, n = 0.
class MyString {
    char *C;
    size_t n;

public:
    MyString() : C( nullptr ), n( 0 ) {}

    MyString( const char *C_ ) {
        n = strlen(  C_ );
        C = new char[ n + 1 ];
        strcpy( C, C_ );
    }

    MyString( const MyString &s ) {
        n = s.n;
        C = new char[ n + 1 ];
        strcpy( C, s.C );
    }

    ~MyString() {
        if ( C ) delete [] C;
    }

    MyString &operator=( const MyString &s );

    friend std::ostream &operator<<( std::ostream &os, const MyString &s );

    MyString operator+( const MyString &s );

    friend MyString operator+( const char* C_, const MyString &s );

    MyString &operator+=( const char* C_ );

    char &operator[]( size_t i );

    MyString operator()( size_t i, size_t n_ );

    bool operator<( const MyString &s );

    bool operator>( const MyString &s );

    bool operator==( const MyString &s );
};

int CompareString( const void *e1, const void *e2 );

void caller();

#endif //HW5_COMPLETE_MY_STRING_H
