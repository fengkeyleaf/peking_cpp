/*
 * where_res_comes_from.h
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

#ifndef HW2_WHERE_RES_COMES_FROM_H
#define HW2_WHERE_RES_COMES_FROM_H

class A {
public:
    int i;

    A( int x ) { i = x; }

    ~A() {
        std::cout << i << std::endl;
    }
};

void caller();

#endif //HW2_WHERE_RES_COMES_FROM_H
