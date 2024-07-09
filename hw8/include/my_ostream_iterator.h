/*
 * my_ostream_iterator.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/6/2024
 */

#include <iostream>
#include <list>
#include <string>
#include <iterator>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW8_MY_OSTREAM_ITERATOR_H
#define HW8_MY_OSTREAM_ITERATOR_H

template<class T1, class T2>
void Copy( T1 s, T1 e, T2 x );

template<class T>
class myostream_iteraotr {
    std::basic_ostream<char>& is;
    const char* d = nullptr;

public:
    myostream_iteraotr( std::basic_ostream<char>& is_, const char* delimit_ ) : is( is_ ), d( delimit_ ) {}

    myostream_iteraotr& operator++() {
        return *this;
    }

    myostream_iteraotr& operator=( const T& v ) {
        is << v;
        if ( d ) is << d;

        return *this;
    }

    myostream_iteraotr& operator*() {
        return *this;
    }
};

void caller();

void sample();

#endif //HW8_MY_OSTREAM_ITERATOR_H
