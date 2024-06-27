/*
 * simple_swap.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include "../include/simple_swap.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */


void swap(
    A &a, A &b
) {
    int tmp = a.x;
    a.x = b.x;
    b.x = tmp;
}

void caller() {
    A a, b;
    a.x = 3;
    b.x = 5;
    swap( a, b );
    std::cout << a.getX() << "," << b.getX();
}