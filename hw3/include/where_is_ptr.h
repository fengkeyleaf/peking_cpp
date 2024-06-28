/*
 * where_is_ptr.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/27/2024
 */

#include <iostream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW3_WHERE_IS_PTR_H
#define HW3_WHERE_IS_PTR_H

struct A {
    int v;

    A( int vv ) : v( vv ) {}

    const A *getPointer() const {
        return this;
    }
};

void caller();

#endif //HW3_WHERE_IS_PTR_H
