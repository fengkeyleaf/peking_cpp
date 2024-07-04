/*
 * fun_and_do_again.h
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

#ifndef HW6_FUN_AND_DO_AGAIN_H
#define HW6_FUN_AND_DO_AGAIN_H

class A {
private:
    int nVal;
public:
    void Fun() { std::cout << "A::Fun" << std::endl; };

    virtual void Do() { std::cout << "A::Do" << std::endl; }
};

class B : public A {
public:
    virtual void Do() { std::cout << "B::Do" << std::endl; }
};

class C : public B {
public:
    void Do() { std::cout << "C::Do" << std::endl; } // virtual

    void Fun() { std::cout << "C::Fun" << std::endl; }
};

void Call( A *p );

void caller();

#endif //HW6_FUN_AND_DO_AGAIN_H