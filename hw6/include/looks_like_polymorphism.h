/*
 * looks_like_polymorphism.h
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

#ifndef HW6_LOOKS_LIKE_POLYMORPHISM_H
#define HW6_LOOKS_LIKE_POLYMORPHISM_H

class B {
private:
    int nBVal;
public:
    void Print() { std::cout << "nBVal=" << nBVal << std::endl; }

    void Fun() { std::cout << "B::Fun" << std::endl; }

    B( int n ) { nBVal = n; }
};

class D: public B {
    int nDVal;
public:
    void Print() {
        B::Print();
        std::cout << "nDVal=" << nDVal << std::endl;
    }

    void Fun() { std::cout << "D::Fun" << std::endl; }

    D( int n ) : B( n * 3 ), nDVal( n ) {}
};

void caller();

#endif //HW6_LOOKS_LIKE_POLYMORPHISM_H
