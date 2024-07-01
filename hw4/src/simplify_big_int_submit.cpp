/*
 * simplify_big_int_submit.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/1/2024
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

using namespace std;
const int MAX = 110;

class CHugeInt {
    const constexpr static char UNITS_CARRY_IN[10] = {
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
    const constexpr static char UNITS[10] = {
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
    char *C;
    size_t s;

    CHugeInt add( const CHugeInt &i ) const {
        size_t n = std::max( s, i.s );
        char C_t[n + 1]; // + 1 to keep the carry-in digit.

        if ( n == s ) add_( *this, i, C_t, n + 1 );
        else add_( i, *this, C_t, n + 1 );

        if ( C_t[ 0 ] == '0' ) {
            char C_f[n];
            std::copy( C_t + 1, C_t + n + 1, C_f );
            return CHugeInt( C_f, n );
        }

        return CHugeInt( C_t, n + 1 );
    }

    static void add_( const CHugeInt &max, const CHugeInt &min, char *C, size_t n ) {

        int idx = n - 1;
        char carry_in = 0;
        for ( int i = min.s - 1; i >= 0; i-- ) {
            char r = max.C[ i + ( max.s - min.s ) ] + min.C[ i ] + carry_in;
            carry_in = r >= 'j' ? 1 : 0;
            C[ idx ] = carry_in == 1 ? UNITS_CARRY_IN[ r % 10 ] : UNITS[ r % 10 ];
            idx--;
        }

        for ( int i = max.s - min.s - 1; i >= 0; i-- ) {
            char r = max.C[ i ] + carry_in;
            carry_in = r >= ':' ? 1 : 0;
            C[ idx ] = carry_in == 1 ? '0' : r;
            idx--;
        }

        C[ idx ] = '0' + carry_in;
    }

    void copy( const CHugeInt &i ) {
        delete[] C;

        s = i.s;
        C = new char[s];
        std::copy( i.C, i.C + s, C );
    }

public:
    CHugeInt() : C( nullptr ), s( 0 ) {}

    CHugeInt( int n ) {
        std::string n_str = std::to_string( n );
        s = n_str.size();
        C = new char[s];
        char const *n_char = n_str.c_str();
        std::copy( n_char, n_char + s, C );
    }

    CHugeInt( const char *S, size_t n ) {
        s = n;
        C = new char[s];
        std::copy( S, S + s, C );
    }

    CHugeInt( const char *S ) {
        s = 0;
        for ( int i = 0; i < 201; i++ ) {
            // trail '\0'
            if ( S[ i ] == '\0' ) break;
            s++;
        }

        C = new char[s];
        std::copy( S, S + s, C );
    }

    CHugeInt( const CHugeInt &i ) {
        C = nullptr;
        s = 0;

        if ( !i.C ) { return; }

        copy( i );
    }

    ~CHugeInt() {
        delete[] C;
    }

    // --------------------------------------------------
    // Operator overloading
    // --------------------------------------------------

    friend CHugeInt operator+( const CHugeInt &a, const CHugeInt &b ) {
        return a.add( b );
    }

    friend CHugeInt operator+( int n, const CHugeInt &i ) {
        return i.add( CHugeInt( n ) );
    }

    friend std::ostream &operator<<( std::ostream &os, const CHugeInt &i ) {
        bool is_padding_zero = true;
        for ( size_t j = 0; j < i.s; j++ ) {
            // Skip padding zeros, like 00012340 => 12340
            if ( i.C[ j ] == '0' && is_padding_zero && j != i.s - 1 ) continue;

            is_padding_zero = false;
            std::cout << i.C[ j ];
        }

        return os;
    }

    CHugeInt &operator+=( int n ) {
        copy( this->add( CHugeInt( n ) ) );
        return *this;
    }

    // https://learn.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170
    CHugeInt &operator++() {
        copy( this->add( CHugeInt( 1 ) ) );
        return *this;
    }

    CHugeInt operator++( int n ) {
        CHugeInt t( *this );
        copy( this->add( CHugeInt( 1 ) ) );
        return t;
    }
};

int main() {
    char s[210];
    int n;

    while ( cin >> s >> n ) {
        CHugeInt a( s );
        CHugeInt b( n );

        cout << a + b << endl;
        cout << n + a << endl;
        cout << a + n << endl;
        b += n;
        cout << ++b << endl;
        cout << b++ << endl;
        cout << b << endl;
    }
    return 0;
}