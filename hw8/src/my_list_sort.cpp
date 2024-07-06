/*
 * my_list.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/6/2024
 */

#include "../include/my_list_sort.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void caller() {
    double a[] = { 1.2, 3.4, 9.8, 7.3, 2.6 };
    std::list<double> lst( a, a + 5 );
    // https://en.cppreference.com/w/cpp/container/list/sort
    // https://en.cppreference.com/w/cpp/utility/functional/greater
    lst.sort( std::greater<double>() );

    for ( std::list<double>::iterator i = lst.begin(); i != lst.end(); ++i )
        std::cout << *i << ",";
}