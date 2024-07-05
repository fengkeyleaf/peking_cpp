/*
 * function_filter.h
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
#include <vector>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW8_FUNCTION_FILTER_H
#define HW8_FUNCTION_FILTER_H

struct A {
    int v;

    A() {}

    A( int n ) : v( n ) {};

    bool operator<( const A &a ) const {
        return v < a.v;
    }
};

// 在此处补充你的代码


template<class T>
void Print( T s, T e );

template<class T1, class T2, class T3>
T2 Filter( T1 s, T1 e, T2 s2, T3 op );

void caller();

#endif //HW8_FUNCTION_FILTER_H
