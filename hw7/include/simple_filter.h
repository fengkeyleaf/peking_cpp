/*
 * simple_filter.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include <iostream>
#include <string>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW7_SIMPLE_FILTER_H
#define HW7_SIMPLE_FILTER_H

template<class T, class F>
T *Filter( T *s, T *e, T *R, F *f );

bool LargerThan2( int n );

bool LongerThan3( std::string s );

void caller();

#endif //HW7_SIMPLE_FILTER_H
