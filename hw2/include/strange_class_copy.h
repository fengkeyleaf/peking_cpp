/*
 * strange_class_copy.h
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

#ifndef PERKING_CPP_STRANGE_CLASS_COPY_H
#define PERKING_CPP_STRANGE_CLASS_COPY_H

class Sample {
public:
    int v;
    Sample() {
        v = 0;
    }
    Sample( int v ) {
        this->v = v;
    }
    Sample( Sample &s ) {
        v = s.v + 2;
    }
};

void PrintAndDouble( Sample o );

void caller();

#endif //PERKING_CPP_STRANGE_CLASS_COPY_H
