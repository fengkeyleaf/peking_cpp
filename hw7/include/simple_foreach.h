/*
 * simple_foreach.h
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

#ifndef HW7_SIMPLE_FOREACH_H
#define HW7_SIMPLE_FOREACH_H

template<class T, class F>
void MyForeach( T *s, T *e, F *f );

void Print( std::string s );

void Inc( int &n );

void caller();

#endif //HW7_SIMPLE_FOREACH_H
