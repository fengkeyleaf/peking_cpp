/*
 * simplify_big_int.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/30/2024
 */

#include "../include/simplify_big_int.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

const int MAX = 110;

// https://www.asciitable.com/
const char CHugeInt::UNITS[ 10 ] = {
    4, // 110
    5, // 111
    6, // 112
    7, // 113
    8, // 114
    10, // undefined
    0, // 106 = '5' + '5' = 53 + 53
    1, // 107
    2, // 108
    3 // 109
};

// TODO: follow-up (1): What if the value is fit into an int?
//  i.e. int + int ( but maybe overflow ), which is more efficient than big + big.
//  So there would be 3 cases: int + int = int or big, int + big = big, big + big = big.
CHugeInt CHugeInt::add( const CHugeInt &i ) const {
    size_t n = std::max( s, i.s );
    char C_t[ n + 1 ];

    if ( n == s ) add_( *this, i, C_t, n + 1 );
    else add_( i, *this, C_t, n + 1 );

    return CHugeInt( C_t );
}

void CHugeInt::add_(
    const CHugeInt &max, const CHugeInt &min, char *C, size_t n
) {
    size_t idx = min.s - 1;
    char carry_in = 0;
    for ( int i = min.s - 1; i >= 0; i-- ) {
        char r = max.C[ i ] + min.C[ i ] + carry_in;
        carry_in = r >= 'j' ? 1 : 0;
        C[ idx ] = UNITS[ r % 10 ];
        assert( C[ idx ] != 10 );
        idx++;
    }

    for ( int i = max.s - min.s - 1; i >= 0; i-- ) {
        char r = max.C[ i ] + carry_in;
        carry_in = r >= 'j' ? 1 : 0;
        C[ idx ] = UNITS[ r % 10 ];
        assert( C[ idx ] != 10 );
        idx++;
    }

    for ( ; idx < n; idx++ ) C[ idx ] = 0;
}

inline void CHugeInt::copy( const CHugeInt &i ) {
    delete [] C;

    s = i.s;
    C = new char[ s ];
    std::copy( i.C, i.C + s, C );
}

// --------------------------------------------------
// Operator overloading
// --------------------------------------------------

CHugeInt operator+( const CHugeInt &a, const CHugeInt &b ) {
    return a.add( b );
}

CHugeInt operator+( int n, const CHugeInt &i ) {
    return i.add( CHugeInt( n ) );
}

std::ostream &operator<<( std::ostream &os, const CHugeInt &i ) {
    bool is_padding_zero = true;
    for ( size_t j = 0; j < i.s; j++ ) {
        if ( i.C[ j ] == '0' && is_padding_zero ) continue;

        is_padding_zero = false;
        std::cout << i.C[ j ];
    }

    return os;
}

CHugeInt &CHugeInt::operator+=( int n ) {
    copy( this->add( CHugeInt( n ) )  );
    return *this;
}

// TODO: follow-up (2): it's a waste of time and space to allocate a new CHugeInt
//  only when we wanna increment it by 1, we can compute it in place.
CHugeInt &CHugeInt::operator++() {
    copy( this->add( CHugeInt( 1 ) )  );
    return *this;
}

CHugeInt &CHugeInt::operator++( int n ) {
    copy( this->add( CHugeInt( 1 ) )  );
    return *this;
}

void caller() {
    char s[ 210 ]; // max: 200
    int n; // 0 ~ 2,147,483,647

    while ( std::cin >> s >> n ) {
        CHugeInt a( s );
        CHugeInt b( n );

        std::cout << a + b << std::endl;
        std::cout << n + a << std::endl;
        std::cout << a + n << std::endl;
        b += n;
        std::cout << ++b << std::endl;
        std::cout << b++ << std::endl;
        std::cout << b << std::endl;
    }
}