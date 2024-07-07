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


class MyMultimap {

};

template<class T>
void Print( T first, T last );

void caller();

#endif //HW9_STUDENT_INFO_H
