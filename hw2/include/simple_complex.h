/*
 * simple_complex.h
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
#include <cstring>
#include <cstdlib>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW2_SIMPLE_COMPLEX_H
#define HW2_SIMPLE_COMPLEX_H

class Complex {
private:
    double r, i;
public:
    void Print() {
        std::cout << r << "+" << i << "i" << std::endl;
    }

    Complex() {
        r = 0;
        i = 0;
    }

    Complex( const char *s ) {
        r = std::stod( std::string( 1, s[ 0 ] ) );
        i = std::stod( std::string( 1, s[ 2 ] ) );
    }
};

void caller();

#endif //HW2_SIMPLE_COMPLEX_H
