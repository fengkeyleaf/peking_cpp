/*
 * main.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/25/2024
 */

#include <iostream>

//#include "./include//simple_swap.h"
//#include "./include/hard_swap.h"
//#include "./include/strange_return.h"
#include "./include/mysterious_init_array.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

class Demo {
    int id;
public:
    Demo( int i ) {
        id = i;
        std::cout << "id=" << id << " Constructed" << std::endl;
    }

    ~Demo() {
        std::cout << "id=" << id << " Destructed" << std::endl;
    }
};

void hw1() {
    // https://www.w3schools.com/cpp/cpp_user_input.asp
    int a, b;
    std::cin >> a;
    std::cin >> b;
    std::cout << a + b << std::endl;
}

//Demo d1( 1 );
void Func() {
    static Demo d2( 2 );
    Demo d3( 3 );
    std::cout << "Func" << std::endl;
}

void classTest() {
    Demo d4( 4 );
    std::cout << &d4 << std::endl;
    d4 = 6;
    std::cout << &d4 << std::endl;
    std::cout << "main" << std::endl;
    Func();
    std::cout << "main ends" << std::endl;
}

int main() {

    test();
//    caller();

    return 0;
}