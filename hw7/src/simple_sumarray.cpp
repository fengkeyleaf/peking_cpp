/*
 * simple_sumarray.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/simple_sumarray.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template <class T>
T SumArray( T *s, T *e ) {
    T t = *s;
    for ( s += 1; s != e; s += 1 ) {
        t += *s;
    }

    return t;
}

void caller() {
    std::string array[4] = { "Tom", "Jack", "Mary", "John" };
    std::cout << SumArray( array, array + 4 ) << std::endl; // TomJackMaryJohn
    int a[4] = { 1, 2, 3, 4 };  //提示：1+2+3+4 = 10
    std::cout << SumArray( a, a + 4 ) << std::endl; // 10
}
