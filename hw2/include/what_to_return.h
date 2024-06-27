/*
 * what_to_return.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include <iostream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW2_WHAT_TO_RETURN_H
#define HW2_WHAT_TO_RETURN_H

class A {
public:
    int val;

    A( int v ) {
        val = v;
    }

    A () {
        val = 123;
    }

    A &GetObj() {
        return *this;
    }
};

void caller();

#endif //HW2_WHAT_TO_RETURN_H
