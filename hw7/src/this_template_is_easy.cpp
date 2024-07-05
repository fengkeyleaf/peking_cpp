/*
 * this_template_is_easy.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include "../include/this_template_is_easy.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void caller() {
    int a[100];
    char line[100];
    while ( std::cin >> line ) {
        myclass<char> obj( line, strlen( line ) );;
        obj.Show();
        int n;
        std::cin >> n;
        for ( int i = 0; i < n; ++i )
            std::cin >> a[ i ];
        myclass<int> obj2( a, n );
        obj2.Show();
    }
}