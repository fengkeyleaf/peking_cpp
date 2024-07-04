/*
 * animal_count.h
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

#ifndef HW6_ANIMAL_COUNT_H
#define HW6_ANIMAL_COUNT_H

class Animal {
public:
    static size_t number;

    Animal() { number++; }

    virtual ~Animal() { number--; }
};

class Dog: public Animal {
public:
    static size_t number;

    Dog() : Animal() { number++; }

    ~Dog() { number--; }
};

class Cat: public Animal {
public:
    static size_t number;

    Cat() : Animal() {
        number++;
    }

    ~Cat() { number--; }
};

void print();

void caller();

#endif //HW6_ANIMAL_COUNT_H
