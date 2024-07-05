/*
 * tricy_3d_array.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include "../include/tricky_3d_array.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T>
typename CArray3D<T>::Array2D &CArray3D<T>::operator[]( size_t i ) {
    return *A[ i ];
}

template<class T>
CArray3D<T>::Array2D::operator T *() {
    return A;
}

CArray3D<int> a( 3, 4, 5 );
CArray3D<double> b( 3, 2, 2 );

void PrintA() {
    for ( int i = 0; i < 3; ++i ) {
        std::cout << "layer " << i << ":" << std::endl;
        for ( int j = 0; j < 4; ++j ) {
            for ( int k = 0; k < 5; ++k )
                std::cout << a[ i ][ j ][ k ] << ",";
            std::cout << std::endl;
        }
    }
}

void PrintB() {
    for ( int i = 0; i < 3; ++i ) {
        std::cout << "layer " << i << ":" << std::endl;
        for ( int j = 0; j < 2; ++j ) {
            for ( int k = 0; k < 2; ++k )
                std::cout << b[ i ][ j ][ k ] << ",";
            std::cout << std::endl;
        }
    }
}

void caller() {
    int No = 0;
    for ( int i = 0; i < 3; ++i ) {
//        a[ i ];
        for ( int j = 0; j < 4; ++j ) {
//            a[ j ][ i ];
            for ( int k = 0; k < 5; ++k )
                a[ i ][ j ][ k ] = No++;
//            a[ j ][ i ][ i ];
        }
    }

//    return;

    // layer 0:
    // 0,1,2,3,4,
    // 5,6,7,8,9,
    // 10,11,12,13,14,
    // 15,16,17,18,19,
    // layer 1:
    // 20,21,22,23,24,
    // 25,26,27,28,29,
    // 30,31,32,33,34,
    // 35,36,37,38,39,
    // layer 2:
    // 40,41,42,43,44,
    // 45,46,47,48,49,
    // 50,51,52,53,54,
    // 55,56,57,58,59,
    PrintA();
    std::memset( a[ 1 ], -1, 20 * sizeof( int ) );
    std::memset( a[ 1 ], -1, 20 * sizeof( int ) );
    // layer 0:
    // 0,1,2,3,4,
    // 5,6,7,8,9,
    // 10,11,12,13,14,
    // 15,16,17,18,19,
    // layer 1:
    // -1,-1,-1,-1,-1,
    // -1,-1,-1,-1,-1,
    // -1,-1,-1,-1,-1,
    // -1,-1,-1,-1,-1,
    // layer 2:
    // 40,41,42,43,44,
    // 45,46,47,48,49,
    // 50,51,52,53,54,
    // 55,56,57,58,59,
    PrintA();
    std::memset( a[ 1 ][ 1 ], 0, 5 * sizeof( int ) );
    // layer 0:
    // 0,1,2,3,4,
    // 5,6,7,8,9,
    // 10,11,12,13,14,
    // 15,16,17,18,19,
    // layer 1:
    // -1,-1,-1,-1,-1,
    // 0,0,0,0,0,
    // -1,-1,-1,-1,-1,
    // -1,-1,-1,-1,-1,
    // layer 2:
    // 40,41,42,43,44,
    // 45,46,47,48,49,
    // 50,51,52,53,54,
    // 55,56,57,58,59,
    PrintA();

    for ( int i = 0; i < 3; ++i )
        for ( int j = 0; j < 2; ++j )
            for ( int k = 0; k < 2; ++k )
                b[ i ][ j ][ k ] = 10.0 / ( i + j + k + 1 );

    // layer 0:
    // 10,5,
    // 5,3.33333,
    // layer 1:
    // 5,3.33333,
    // 3.33333,2.5,
    // layer 2:
    // 3.33333,2.5,
    // 2.5,2,
    PrintB();
    int n = a[ 0 ][ 1 ][ 2 ];
    double f = b[ 0 ][ 1 ][ 1 ];
    // ****
    // 7,3.33333
    std::cout << "****" << std::endl;
    std::cout << n << "," << f << std::endl;
}
