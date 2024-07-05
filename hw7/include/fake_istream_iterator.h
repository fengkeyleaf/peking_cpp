/*
 * fake_istream_iterator.h
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
#include <string>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW7_FAKE_ISTREAM_ITERATOR_H
#define HW7_FAKE_ISTREAM_ITERATOR_H

// https://stackoverflow.com/questions/52479124/why-stdistream-iterator-constructor-returning-pointer
template<class T>
class CMyistream_iterator {
    T v;
    std::istream &is;

public:
    CMyistream_iterator( std::istream &is_ ) : is( is_ ) { is >> v; }

    T &operator*();

    CMyistream_iterator<T> operator++( int n );
};

void caller();

void sample();

#endif //HW7_FAKE_ISTREAM_ITERATOR_H
