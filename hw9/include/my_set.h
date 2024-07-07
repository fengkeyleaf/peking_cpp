/*
 * my_set.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/7/2024
 */

#include <fstream>
#include <iostream>
#include <map>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW9_MY_SET_H
#define HW9_MY_SET_H

class MySet {
    // https://en.cppreference.com/w/cpp/container/multiset
    std::map<int, size_t> M;

public:
    void add( int x );

    void del( int x );

    void ask( int x );
};

void caller();

#endif //HW9_MY_SET_H
