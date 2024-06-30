/*
 * suprising_print_out.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include "../include/surprising_print_out.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

std::istream &operator>>( std::istream& is, Point &p ) {
    std::cin >> p.x;
    std::cin >> p.y;
    return is;
}

std::ostream &operator<<( std::ostream& os, const Point &p ) {
    std::cout << p.x << "," << p.y;
    return os;
}

void caller() {
    Point p;
    while ( std::cin >> p ) {
        std::cout << p << std::endl;
    }
}