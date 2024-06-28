/*
 * where_is_ptr.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/27/2024
 */

#include "../include/where_is_ptr.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void caller() {
    const A a( 10 );
    const A *p = a.getPointer();
    std::cout << p->v << std::endl; // 10
}