/*
 * delete_like_this.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include <iostream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW6_DELETE_LIKE_THIS_H
#define HW6_DELETE_LIKE_THIS_H

class A {
public:
    A() {}

    virtual ~A() { std::cout << "destructor A" << std::endl; }
};

class B : public A {
public:
    ~B() { std::cout << "destructor B" << std::endl; }
};

void caller();

#endif //HW6_DELETE_LIKE_THIS_H
