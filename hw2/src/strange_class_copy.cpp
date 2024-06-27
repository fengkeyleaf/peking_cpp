/*
 * strange_class_copy.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include "../include/strange_class_copy.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void PrintAndDouble( Sample o ) {
    std::cout << o.v;
    std::cout << std::endl;
}

void caller() {
    Sample a( 5 );
    Sample b = a;
    PrintAndDouble( b );
    Sample c = 20;
    PrintAndDouble( c );
    Sample d;
    d = a;
    // 9
    // 22
    // 5
    std::cout << d.v;
}