/*
 * simple_swap.h
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

#ifndef HW1_SIMPLE_SWAP_H
#define HW1_SIMPLE_SWAP_H

class A {
public:
    int x;

    int getX() { return x; }
};

void swap(
        A &a, A &b
);
void caller();

#endif //HW1_SIMPLE_SWAP_H
