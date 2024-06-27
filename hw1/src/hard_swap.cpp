/*
 * hard_swap.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include "../include/hard_swap.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void swap(
        int *&a, int *&b
) {
    int *tmp = a;
    a = b;
    b = tmp;
}

void caller() {
    int a = 3, b = 5;
    int *pa = &a;
    int *pb = &b;
    swap( pa, pb );
    std::cout << *pa << "," << *pb;
}