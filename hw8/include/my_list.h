/*
 * my_list.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/6/2024
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW8_MY_LIST_H
#define HW8_MY_LIST_H

template<class T>
class MyVector {
    // https://en.cppreference.com/w/cpp/container/map
    std::map<size_t, std::vector<T>> M;
    const std::ofstream fo = std::ofstream( "/home/sora/perking_cpp/hw8/out_list_test.txt" );

public:
    void append( size_t id, T& t_ );

    void add_new_list( size_t id_ );

    void merge( size_t id1, size_t id2 );

    void print( size_t id );

    void unique( size_t id );

    void redirect_to_file();
};

void caller();

#endif //HW8_MY_LIST_H
