/*
 * animal_count.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/animal_count.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

size_t Animal::number = 0;
size_t Dog::number = 0;
size_t Cat::number = 0;

void print() {
    std::cout << Animal::number << " animals in the zoo, " << Dog::number << " of them are dogs, " << Cat::number
              << " of them are cats" << std::endl;
}

void caller() {
    // 0 animals in the zoo, 0 of them are dogs, 0 of them are cats
    print();
    Dog d1, d2;
    Cat c1;
    // 3 animals in the zoo, 2 of them are dogs, 1 of them are cats
    print();
    Dog *d3 = new Dog();
    Animal *c2 = new Cat;
    Cat *c3 = new Cat;
    // 6 animals in the zoo, 3 of them are dogs, 3 of them are cats
    print();
    delete c3;
    delete c2;
    delete d3;
    // 3 animals in the zoo, 2 of them are dogs, 1 of them are cats
    print();
}