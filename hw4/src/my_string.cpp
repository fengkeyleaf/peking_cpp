/*
 * my_string.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include "../include/my_string.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

std::ostream &operator<<( std::ostream &os, const MyString &s ) {
    std::cout << s.p;
    return os;
}

void caller() {
    char w1[200], w2[100];
    while ( std::cin >> w1 >> w2 ) {
        MyString s1( w1 ), s2 = s1;
        MyString s3( NULL );
        s3.Copy( w1 );
        std::cout << s1 << "," << s2 << "," << s3 << std::endl;

        s2 = w2;
        s3 = s2;
        s1 = s3;
        std::cout << s1 << "," << s2 << "," << s3 << std::endl;
    }
}