/*
 * inherited_my_string.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/2/2024
 */

#include "../include/inherited_my_string.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// -----------------------------------------------------
// class MyString
// -----------------------------------------------------

MyString operator+( const MyString &s1, const MyString &s2 ) {
    std::string t = ( std::string ) s1 + ( std::string ) s2;
    return MyString( t );
}

MyString operator+( const char *C, const MyString &s ) {
    std::string t = C + ( std::string ) s;
    return MyString( t );
}

MyString operator+( const MyString &s, const char *C ) {
    std::string t = ( std::string ) s + C;
    return MyString( t );
}

MyString MyString::operator()( size_t i, size_t n ) {
    // https://www.geeksforgeeks.org/substring-in-cpp/
    std::string t = substr( i, n );
    return MyString( t );
}

// -----------------------------------------------------
// helper functions
// -----------------------------------------------------

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
//    std::cout << "10. " << s2 << std::endl;
//    std::cout << "10. " << s2 + s4 << std::endl;
//    std::cout << "10. " << s2 + s4 + " uvw " << std::endl;
//    std::cout << "10. " << s2 + s4 + " uvw " + "xyz" << std::endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    std::cout << "11. " << s1 << std::endl;
    sort( SArray, SArray + 4 );
    for ( int i = 0; i < 4; i++ )
        std::cout << SArray[ i ] << std::endl;
    //s1的从下标0开始长度为4的子串
    std::cout << s1( 0, 4 ) << std::endl;
    //s1的从下标5开始长度为10的子串
    std::cout << s1( 5, 10 ) << std::endl;
}
