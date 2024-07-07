/*
 * my_set_submit.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/7/2024
 */

#include <fstream>
#include <iostream>
#include <map>


/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

class MySet {
    // https://en.cppreference.com/w/cpp/container/multiset
    std::map<int, size_t> M;

public:
    void add( int x ) {
        if ( M.find( x ) == M.end() ) M[ x ] = 0; // add a container for x;

        std::cout << ++M[ x ] << std::endl;
    }

    void del( int x ) {
        if ( M.find( x ) == M.end() ) {
            std::cout << 0 << std::endl;
            return;
        }

        size_t n = M[ x ];
        M[ x ] = 0;
        std::cout << n << std::endl;
    }

    void ask( int x ) {
        if ( M.find( x ) == M.end() ) {
            std::cout << 0 << " " << 0 << std::endl;
            return;
        }

        std::cout << 1 << " " << M[ x ] << std::endl;
    }
};

void caller() {
    MySet S;

    int n;
    std::cin >> n;
    while ( n-- ) {
        int x;
        std::string s;
        std::cin >> s;
        if ( s == "add" ) {
            std::cin >> x;
            S.add( x );
        }
        else if ( s == "del" ) {
            std::cin >> x;
            S.del( x );
        }
        else if ( s == "ask" ) {
            std::cin >> x;
            S.ask( x );
        }
    }
}

int main() {

    caller();

    return 0;
}