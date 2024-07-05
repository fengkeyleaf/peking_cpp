/*
 * this_template_is_easy.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include <iostream>
#include <string>
#include <cstring>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW7_THIS_TEMPLATE_IS_EASY_H
#define HW7_THIS_TEMPLATE_IS_EASY_H

template<class T>
class myclass {
    T *p;
    size_t size;

public:
    myclass( const T* C_, size_t n_ ) {
        size = n_;
        p = new T[ n_ ];
        std::copy( C_, C_ + n_, p );
    }

    ~myclass() {
        delete[] p;
    }

    void Show() {
        for ( int i = 0; i < size; i++ ) {
            std::cout << p[ i ] << ",";
        }
        std::cout << std::endl;
    }
};

void caller();

#endif //HW7_THIS_TEMPLATE_IS_EASY_H
