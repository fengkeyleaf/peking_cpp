/*
 * function_filter.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include "../include/function_filter.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

std::ostream &operator<<( std::ostream &o, A &a ) {
    o << a.v;
    return o;
}

template<class T>
void Print( T s, T e ) {
    for ( ; s != e; ++s )
        std::cout << *s << ",";
    std::cout << std::endl;
}

template<class T1, class T2, class T3>
T2 Filter( T1 s, T1 e, T2 s2, T3 op ) {
    for ( ; s != e; ++s ) {
        if ( op( *s ) ) {
            *s2 = *s;
            ++s2;
        }
    }
    return s2;
}

void caller() {
    std::vector<int> ia;
    std::vector<A> aa;

    int m, n;
    while ( std::cin >> m >> n ) {
        ia.clear();
        aa.clear();
        int k, tmp;
        std::cin >> k;
        for ( int i = 0; i < k; ++i ) {
            std::cin >> tmp;
            ia.push_back( tmp );
            aa.push_back( tmp );
        }
        std::vector<int> ib( k );
        std::vector<A> ab( k );
        std::vector<int>::iterator p = Filter( ia.begin(), ia.end(), ib.begin(), FilterClass<int>( m, n ) );
        Print( ib.begin(), p );
        std::vector<A>::iterator pp = Filter( aa.begin(), aa.end(), ab.begin(), FilterClass<A>( m, n ) );
        Print( ab.begin(), pp );
    }
}