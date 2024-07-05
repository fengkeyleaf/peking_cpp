/*
 * sort_again.h
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

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW7_SORT_AGAIN_H
#define HW7_SORT_AGAIN_H

#define NUM 5

bool Greater2( int n1, int n2 );

bool Greater1( int n1, int n2 );

bool Greater3( double d1, double d2 );

template<class T1, class T2>
void mysort( T1 *s, T1 *e, T2 *f );

void caller();

#endif //HW7_SORT_AGAIN_H
