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
const char CHugeInt::UNITS_CARRY_IN[ 10 ] = {
    '4', // 110
    '5', // 111
    '6', // 112
    '7', // 113
    '8', // 114
    '9', // 115
    '0', // 106 = '5' + '5' = 53 + 53
    '1', // 107
    '2', // 108
    '3' // 109
};

const char CHugeInt::UNITS[ 10 ] = {
    '4', // 100
    '5', // 101
    '6', // 102
    '7', // 103
    '8', // 104
    '9', // 105
    '0', // 96 = '0' + '0' = 48 + 48 = 96
    '1', // 97
    '2', // 98
    '3' // 99
};

// TODO: follow-up (1): What if the value is fit into an int?
//  i.e. int + int ( but maybe overflow ), which is more efficient than big + big.
//  So there would be 3 cases: int + int = int or big, int + big = big, big + big = big.
CHugeInt CHugeInt::add( const CHugeInt &i ) const {
    size_t n = std::max( s, i.s );
    char C_t[ n + 1 ]; // + 1 to keep the carry-in digit.

    if ( n == s ) add_( *this, i, C_t, n + 1 );
    else add_( i, *this, C_t, n + 1 );

    if ( C_t[ 0 ] == '0' ) {
        char C_f[ n ];
        std::copy( C_t + 1, C_t + n + 1, C_f );
        return CHugeInt( C_f, n );
    }

    return CHugeInt( C_t, n + 1 );
}

void CHugeInt::add_(
    const CHugeInt &max, const CHugeInt &min, char *C, size_t n
) {
    assert( max.s >= min.s );

    int idx = n - 1;
    char carry_in = 0;
    for ( int i = min.s - 1; i >= 0; i-- ) {
        char r = max.C[ i + ( max.s - min.s ) ] + min.C[ i ] + carry_in;
        carry_in = r >= 'j' ? 1 : 0;
        C[ idx ] = carry_in == 1 ? UNITS_CARRY_IN[ r % 10 ] : UNITS[ r % 10 ];
        assert( C[ idx ] < ':' );
        idx--;
    }

    for ( int i = max.s - min.s - 1; i >= 0; i-- ) {
        char r = max.C[ i ] + carry_in;
        carry_in = r >= ':' ? 1 : 0;
        C[ idx ] = carry_in == 1 ? '0' : r;
        assert( C[ idx ] < ':' );
        idx--;
    }

    assert( idx == 0 );
    C[ idx ] = '0' + carry_in;
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
        // Skip padding zeros, like 00012340 => 12340
        if ( i.C[ j ] == '0' && is_padding_zero && j != i.s - 1 ) continue;

        is_padding_zero = false;
        std::cout << i.C[ j ];
    }

    return os;
}

CHugeInt &CHugeInt::operator+=( int n ) {
    copy( this->add( CHugeInt( n ) ) );
    return *this;
}

// TODO: follow-up (2): it's a waste of time and space to allocate a new CHugeInt
//  only when we wanna increment it by 1, we can compute it in place.
CHugeInt &CHugeInt::operator++() {
    copy( this->add( CHugeInt( 1 ) ) );
    return *this;
}

// https://stackoverflow.com/a/15244185
CHugeInt CHugeInt::operator++( int n ) {
    CHugeInt t( *this );
    copy( this->add( CHugeInt( 1 ) ) );
    return t;
}

// test cases:
// 1) 0, 0
// 0
// 0
// 0
// 0
// 1
// 1
// 2
// 2) 6, 0
// 6
// 6
// 6
// 1
// 1
// 2
// 3) 0, 6
// 6
// 6
// 6
// 13
// 13
// 14
// 4) 18, 1
// 19
// 19
// 19
// 3
// 3
// 4
// 5) 1, 18
// 19
// 19
// 19
// 37
// 37
// 38
// 6) 34, 27
// 61
// 61
// 61
// 55
// 55
// 56
// 7) 2147483647, 0
// 2147483647
// 2147483647
// 2147483647
// 1
// 1
// 2
// 8) 0, 2147483647
// 2147483647
// 2147483647
// 2147483647
// 4294967295
// 4294967295
// 4294967296
// 9) 2147483647, 1
// 2147483648
// 2147483648
// 2147483648
// 3
// 3
// 4
// 10) 1, 2147483647
// 2147483648
// 2147483648
// 2147483648
// 4294967295
// 4294967295
// 4294967296
// 11) 2147483648, 0
// 2147483648
// 2147483648
// 2147483648
// 1
// 1
// 2
// 12) 99999999999999999999999999888888888888888812345678901234567789, 12
// 99999999999999999999999999888888888888888812345678901234567801
// 99999999999999999999999999888888888888888812345678901234567801
// 99999999999999999999999999888888888888888812345678901234567801
// 25
// 25
// 26
// 13) MAX_s, 2147483647
// MAX_s = 999 ... 999, 200 digits.
// 1 ... 02147483646, 201 digits
// 1 ... 02147483646, 201 digits
// 1 ... 02147483646, 201 digits
// 4294967295
// 4294967295
// 4294967296

void getMaxInput( char *s, size_t n ) {
    for ( size_t i = 0; i < 200; i++ )
        s[ i ] = '9';

    s[ 200 ] = '\0';
}

void caller() {
    char s[ 210 ]; // max: 200
    int n; // 0 ~ 2,147,483,647

    // https://stackoverflow.com/questions/29477567/using-cin-for-char-array
    while ( std::cin >> s >> n ) {
//        getMaxInput( s, 210 );
//        n = 2147483647;

        CHugeInt a( s );
        CHugeInt b( n );

//        std::cout << a << std::endl;
//        std::cout << b << std::endl;

        std::cout << a + b << std::endl;
        std::cout << n + a << std::endl;
        std::cout << a + n << std::endl;
        b += n;
        std::cout << ++b << std::endl;
        std::cout << b++ << std::endl;
        std::cout << b << std::endl;
    }
}