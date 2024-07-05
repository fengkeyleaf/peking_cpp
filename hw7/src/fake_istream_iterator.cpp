/*
 * fake_istream_iterator.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include <iterator>
#include "../include/fake_istream_iterator.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T>
T &CMyistream_iterator<T>::operator*() {
    return v;
}

template<class T>
CMyistream_iterator<T> CMyistream_iterator<T>::operator++( int n ) {
    CMyistream_iterator t = *this;
    is >> v;
    return t;
}

void caller() {
    int t;
    std::cin >> t;
    while ( t-- ) {
        CMyistream_iterator<int> inputInt( std::cin );
        int n1, n2, n3;
        n1 = *inputInt; //读入 n1
        int tmp = *inputInt;
        std::cout << tmp << std::endl;
        inputInt++;
        n2 = *inputInt; //读入 n2
        inputInt++;
        n3 = *inputInt; //读入 n3
        std::cout << n1 << " " << n2 << " " << n3 << " ";
        CMyistream_iterator<std::string> inputStr( std::cin );
        std::string s1, s2;
        s1 = *inputStr;
        inputStr++;
        s2 = *inputStr;
        std::cout << s1 << " " << s2 << std::endl;
    }
}

void sample() {
//    std::istream_iterator inputInt( std::cin );
//    std::cout << *inputInt << ",";
//    inputInt++;
//    inputInt++;
//    std::cout << *inputInt;
}