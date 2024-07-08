/*
 * student_info.h
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
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW9_STUDENT_INFO_H
#define HW9_STUDENT_INFO_H

struct Student {
    std::string name;
    int score;
};

// https://en.cppreference.com/w/cpp/utility/pair/make_pair
// https://en.cppreference.com/w/cpp/container/multimap
template<class Key, class T, class Compare = std::greater<Key>>
class MyMultimap {
    std::multimap<Key, T, Compare> M;

public:
    MyMultimap() { M.begin()->second; }

    // https://www.geeksforgeeks.org/implementing-iterator-pattern-of-a-single-linked-list/
    class iterator {
        typename std::multimap<Key, T, Compare>::iterator iter;

    public:
        explicit iterator( typename std::multimap<Key, T, Compare>::iterator iter_ ) : iter( iter_ ) {}

        bool operator!=( const iterator& iter_ );

        typename std::multimap<Key, T, Compare>::iterator operator->();

        iterator& operator++();

        std::string operator*();
    };

    void insert( std::pair<Key, T> p );

    void Set( Key k, T v );

    void clear();

    MyMultimap<Key, T, Compare>::iterator begin();

    MyMultimap<Key, T, Compare>::iterator end();

    // https://en.cppreference.com/w/cpp/container/multimap/find
    MyMultimap<Key, T, Compare>::iterator find( const Key& k );
};

template<class T>
void Print( T first, T last );

void caller();

#endif //HW9_STUDENT_INFO_H
