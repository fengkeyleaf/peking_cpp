/*
 * strange_operator_overload.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include <iostream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW4_STRANGE_OPERATOR_OVERLOAD_H
#define HW4_STRANGE_OPERATOR_OVERLOAD_H

class MyInt {
    int nVal;
public:
    MyInt( int n ) { nVal = n; }

    MyInt &operator-( int n ) {
        nVal -= n;
        return *this;
    }

    // https://www.tutorialspoint.com/cplusplus/function_call_operator_overloading.htm
    // friend int Inc( int n ); // Unnecessary
    friend int Inc( MyInt &i ) {
        return i.nVal + 1;
    }
};

void caller();

#endif //HW4_STRANGE_OPERATOR_OVERLOAD_H
