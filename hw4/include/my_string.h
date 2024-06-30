/*
 * my_string.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include <iostream>
#include <string>
#include <cstring>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW4_MY_STRING_H
#define HW4_MY_STRING_H

class MyString {
public:
    char *p;
    MyString( const char *s ) {
        if ( s ) {
            std::cout << "Type convert before: " << " | " << "addr: " << &p << std::endl;
            p = new char[ strlen( s ) + 1 ];
            strcpy( p, s );
            std::cout << "Type convert after: " <<  p << " | " << "addr: " << &p << std::endl;
        } else
            p = NULL;
    }

    MyString( const MyString &s ) {
        if ( !s.p ) {
            p = nullptr;
            return;
        }

        std::cout << "Copy constructor before: " << " | " << "addr: " << &p << std::endl;
        p = new char[ strlen( s.p ) + 1 ];
        strcpy( p, s.p );
        std::cout << "Copy constructor after: " <<  p << " | " << "addr: " << &p << std::endl;
    }

    ~MyString() {
        if ( p ) {
            std::cout << "free: " << p << " | " << "addr: " << &p << std::endl;
            delete[] p;
        }
    }

    void Copy( const char *s ) {
        if ( p ) delete[] p;

        p = new char[ strlen( s ) + 1 ];
        strcpy( p, s );
        std::cout << "Copy after: " <<  p << " | " << "addr: " << &p << std::endl;
    }

    // https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend std::ostream & operator<< ( std::ostream& os, const MyString &s );

    // https://stackoverflow.com/questions/61488932/does-conversion-constructor-create-an-object-and-destroys-it-if-there-is-no-assi
    MyString &operator= ( const MyString &s ) {
        if ( p ) delete[] p;

        p = new char[ strlen( s.p ) + 1 ];
        strcpy( p, s.p );

        return *this;
    }
};

void caller();

#endif //HW4_MY_STRING_H
