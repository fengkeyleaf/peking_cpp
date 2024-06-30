/*
 * suprising_print_out.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include <iostream>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW4_SURPRISING_PRINT_OUT_H
#define HW4_SURPRISING_PRINT_OUT_H

class Point {
private:
    int x;
    int y;
public:
    Point() {};

    friend std::istream &operator>>( std::istream& is, Point &p );
    friend std::ostream &operator<<( std::ostream& os, const Point &p );
};

void caller();

#endif //HW4_SURPRISING_PRINT_OUT_H
