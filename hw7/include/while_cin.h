/*
 * while_cin.h
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

#ifndef HW7_WHILE_CIN_H
#define HW7_WHILE_CIN_H

// https://stackoverflow.com/questions/12923762/c-how-does-while-cin-x-work
// https://stackoverflow.com/questions/6242768/is-the-safe-bool-idiom-obsolete-in-c11
class MyCin {
    bool f = true;

public:
    MyCin &operator>>( int &n );

    explicit operator bool() const;
};

void caller();

#endif //HW7_WHILE_CIN_H
