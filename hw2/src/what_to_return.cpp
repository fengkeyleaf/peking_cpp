/*
 * what_to_return.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include "../include/what_to_return.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// 123
// 2
// 3
// 4
// 5

void caller() {
    int m,n;
    A a;
    std::cout << a.val << std::endl;
    int id = 0;
    while( id++ < 2 ) { // 2 3 // 4 5
        if ( id == 1 ) {
            m = 2;
            n = 3;
        }
        else {
            m = 4;
            n = 5;
        }
        a.GetObj() = m;
        std::cout << a.val << std::endl;
        a.GetObj() = A( n );
        std::cout << a.val<< std::endl;
    }
}