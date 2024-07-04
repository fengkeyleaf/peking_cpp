/*
 * inherited_my_string.h
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
#include <string>
#include <algorithm>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW5_INHERITED_MY_STRING_H
#define HW5_INHERITED_MY_STRING_H

// Hints:
// 1st try: s1 = "ijkl-"; => Use of overloaded operator '=' is ambiguous (with operand types 'MyString' and 'const char[6]')
//    std::string &operator=( const std::string &s );

// 2nd try: 4 = "qrst-" + s2; => No viable overloaded '='
//    MyString operator+( const MyString &s );
// s1 = s2 + s4 + " uvw " + "xyz"; => Use of overloaded operator '+' is ambiguous (with operand types 'MyString' and 'const char[6]')
//    friend MyString operator+( const char *C, const MyString &s );

// template<typename _CharT, typename _Traits, typename _Alloc>
//    basic_string<_CharT, _Traits, _Alloc>
//    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
//	      const basic_string<_CharT, _Traits, _Alloc>& __rhs)

class MyString : public std::string {
    MyString( std::string &s ) : std::string( s ) {}

public:
    MyString(): std::string() {}

    MyString( const char *C_ ): std::string( C_ ) {}

    MyString( const MyString &s ) : std::string( s ) {}

    friend MyString operator+( const MyString &s1, const MyString &s2 );

    friend MyString operator+( const char *C, const MyString &s );

    friend MyString operator+( const MyString &s, const char *C );

    MyString operator()( size_t i, size_t n );
};

void caller();

#endif //HW5_INHERITED_MY_STRING_H
