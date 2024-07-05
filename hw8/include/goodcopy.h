/*
 * goodcopy.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include <cassert>
#include <iostream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW8_GOODCOPY_H
#define HW8_GOODCOPY_H

template<class T>
struct GoodCopy {
public:
    void operator()( T *s, T *e, T *D );
};

template<class T>
void Print( T s, T e );

void caller();

#endif //HW8_GOODCOPY_H
