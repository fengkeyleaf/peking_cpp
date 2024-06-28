/*
 * mysterious_init_array.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/26/2024
 */

#include "../include/mysterious_init_array.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void test() {
    // a 等价 b
    int *a; // 表示一个int值的地址，或者一个一维数组中第一个值的地址
    int b[ 1 ]; // 表示一个长度为1的一维数组
    a = b; // 不会编译错误
    auto c = b; // int *c

    // d 等价 e
    int **d; // 表示一个二维数组的第一个值的地址
    int *e[ 1 ]; // 表示一个长度为1二维数组的指针
    int f[ 2 ][ 1 ]; // 表示一个长度为2*1的二维数组
    auto g = e; // int **g
    auto h = f; // int (*h)[ 1 ]
    d = e; // 不会编译错误

    int (*i)[ 1 ]; // 表示一个指向多维数组的指针
    // d = i; // 编译错误： Incompatible pointer types assigning to 'int **' from 'int (*)[1]'
    i = h; // 不会编译错误
    i = &b; // 不会编译错误

    // Example of data_type (*var_name)[size_of_array];
    int arr[ 3 ][ 4 ] = { { 10, 11, 12, 13 },
                      { 20, 21, 22, 23 },
                      { 30, 31, 32, 33 } };
    int (*ptr)[ 4 ];
    ptr = arr;
    // 几种方法用于访问位于arr的第二行，第三个的元素：
    std::cout << ( arr[ 1 ][ 2 ] ) << std::endl; // 22
    std::cout << ( *( ptr + 1 ) )[ 2 ] << std::endl; // 22
    std::cout << *( *( ptr + 1 ) + 2 ) << std::endl; // 22
    std::cout << *( ( ptr + 1 )[ 2 ] )<< std::endl; // Undefined value

    std::cout << ptr << std::endl; // Base address, 0x7fff6dbf2d70
    std::cout << ( ptr + 1 ) << std::endl; // 0x7fff6dbf2d80, offset by 16 bytes compared to the base addr, which is the size of one row, which is 4 integers.
    std::cout << &( ptr[ 1 ] ) << std::endl; // 0x7fff6dbf2d80, same as the previous one.
    std::cout << ( *( ptr + 1 ) + 2 ) << std::endl; // 0x7fff6dbf2d88, offset by 24 bytes compared to the base, which is the the size of 6 integers before 22

    // 更多内容，有兴趣的童鞋可以参考下面文章：
    // https://www.geeksforgeeks.org/pointer-array-array-pointer/
    // https://stackoverflow.com/questions/8108416/excess-elements-of-scalar-initializer-for-pointer-to-array-of-ints
}

// https://stackoverflow.com/questions/8108416/excess-elements-of-scalar-initializer-for-pointer-to-array-of-ints
// https://www.geeksforgeeks.org/pointer-array-array-pointer/
void caller() {
    int *a[] = {
            nullptr,
            new int[6] { 1, 2, 3, 4, 5, 6 },
            new int[6] { 1, 2, 3, 4, 5, 6 },
            new int[6] { 1, 2, 3, 4, 5, 6 }
    };

    *a[ 2 ] = 123;
    a[ 3 ][ 5 ] = 456;
    if ( !a[ 0 ] ) {
        std::cout << *a[ 2 ] << "," << a[ 3 ][ 5 ]; // 123,456
    }
}