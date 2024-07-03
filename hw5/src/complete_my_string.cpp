/*
 * complete_my_string.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/2/2024
 */

#include "../include/complete_my_string.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// -----------------------------------------------------
// class MyString
// -----------------------------------------------------

MyString &MyString::operator=( const MyString &s ) {
    if ( C ) delete [] C;

    n = s.n;
    C = new char[ s.n + 1 ];
    strcpy( C, s.C );
    return *this;
}

std::ostream &operator<<( std::ostream &os, const MyString &s ) {
    if ( s.n > 0 ) std::cout << s.C;
    return os;
}

// Not good to return a reference.
MyString MyString::operator+( const MyString &s ) {
    char t[ n + s.n + 1 ];
    strcpy( t, C );
    strcat( t, s.C );

    return MyString ( t );
}

MyString operator+( const char *C_, const MyString &s ) {
    char t[ strlen( C_ ) + s.n + 1 ];
    strcpy( t, C_ );
    strcat( t, s.C );

    return MyString ( t );
}

MyString &MyString::operator+=( const char *C_ ) {
    char *t = C;
    C = new char[ strlen( C_ ) + n + 1 ];

    strcpy( C, t );
    strcat( C, C_ );

    delete [] t;
    return *this;
}

char &MyString::operator[]( size_t i ) {
    return C[ i ];
}

// TODO: Follow-up 2): Deal with index out of boundary. e.g. "123"(4,5) => No such a substring.
MyString MyString::operator()( size_t i, size_t n_ ) {
    if ( i >= n ) return MyString();

    size_t j = i + n_ - 1 >= n ? n - 1 : i + n_ - 1;
    char t[ j - i + 1 + 1 ];
    size_t k = i;
    for ( ; k <= j; k++ ) {
        t[ k - i ] = C[ k ];
    }
    t[ k - i ] = '\0';

    return MyString( t );
}

bool MyString::operator<( const MyString &s ) {
    return strcmp( C, s.C ) == -1;
}

bool MyString::operator>( const MyString &s ) {
    return strcmp( C, s.C ) == 1;
}

bool MyString::operator==( const MyString &s ) {
    return strcmp( C, s.C ) == 0;
}

// -----------------------------------------------------
// helper functions
// -----------------------------------------------------

int strlen( const char *s ) {
    int i = 0;
    for ( ; s[ i ]; ++i );
    return i;
}

void strcpy( char *d, const char *s ) {
    int i = 0;
    for ( i = 0; s[ i ]; ++i )
        d[ i ] = s[ i ];
    d[ i ] = 0;

}

int strcmp( const char *s1, const char *s2 ) {
    for ( int i = 0; s1[ i ] && s2[ i ]; ++i ) {
        if ( s1[ i ] < s2[ i ] )
            return -1;
        else if ( s1[ i ] > s2[ i ] )
            return 1;
    }
    return 0;
}

void strcat( char *d, const char *s ) {
    int len = strlen( d );
    strcpy( d + len, s );
}

int CompareString( const void *e1, const void *e2 ) {
    MyString *s1 = ( MyString * ) e1;
    MyString *s2 = ( MyString * ) e2;
    if ( *s1 < *s2 )
        return -1;
    else if ( *s1 == *s2 )
        return 0;
    else
        return 1;
}

void caller() {
    MyString s1( "abcd-" ), s2, s3( "efgh-" ), s4( s1 );
    MyString SArray[4] = { "big", "me", "about", "take" };
    std::cout << "1. " << s1 << s2 << s3 << s4 << std::endl;
    s4 = s3;
    s3 = s1 + s3;
    std::cout << "2. " << s1 << std::endl;
    std::cout << "3. " << s2 << std::endl;
    std::cout << "4. " << s3 << std::endl;
    std::cout << "5. " << s4 << std::endl;
    std::cout << "6. " << s1[ 2 ] << std::endl;
    s2 = s1;
    s1 = "ijkl-";
    s1[ 2 ] = 'A';
    std::cout << "7. " << s2 << std::endl;
    std::cout << "8. " << s1 << std::endl;
    s1 += "mnop";
    std::cout << "9. " << s1 << std::endl;
    s4 = "qrst-" + s2;
    std::cout << "10. " << s4 << std::endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    std::cout << "11. " << s1 << std::endl;
    qsort( SArray, 4, sizeof( MyString ), CompareString );
    for ( int i = 0; i < 4; i++ )
        std::cout << SArray[ i ] << std::endl;
    //s1的从下标0开始长度为4的子串
    std::cout << s1( 0, 4 ) << std::endl;
    //s1的从下标5开始长度为10的子串
    std::cout << s1( 5, 10 ) << std::endl;
}
