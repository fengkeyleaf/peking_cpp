/*
 * tricy_3d_array.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/5/2024
 */

#include <iostream>
#include <iomanip>
#include <cstring>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW8_TRICY_3D_ARRAY_H
#define HW8_TRICY_3D_ARRAY_H

template<class T>
class CArray3D {
    // https://github.com/fengkeyleaf/peking_cpp/blob/master/hw4/include/twoD_array.h
    class Array2D {
        size_t r;
        size_t c;
        T *A;

    public:
        Array2D() {
            r = c = 0;
            A = nullptr;
        }

        Array2D( size_t r, size_t c ) {
            this->r = r;
            this->c = c;
            A = new T[ r * c ];
        }

        ~Array2D() {
            if ( A ) delete [] A;
        }

        T *operator[]( size_t r ) {
            return r * c + A;
        }

        T &operator()( size_t r, size_t c ) {
            return A[ r * this->c + c ];
        }

        Array2D &operator=( const Array2D &A ) {
            if ( this->A ) delete [] this->A;

            c = A.c;
            r = A.r;
            size_t s = A.c * A.r;
            this->A = new int[ s ];
            std::copy( A.A, A.A + s, this->A );
            return *this;
        }

        operator T*();
    };

    Array2D **A;
    size_t i;

public:
    CArray3D( size_t i_, size_t j_, size_t k_ ) {
        i = i_;
        A = new Array2D*[ i ];
        for ( size_t j = 0; j < i_; j++ )
            A[ j ] = new Array2D( j_, k_ );
    }

    ~CArray3D() {
        for ( size_t i_ = 0; i_ < i; i_++ )
            delete A[ i_ ];

        delete [] A;
    }

    Array2D &operator[]( size_t i );
};

void PrintA();

void PrintB();

void caller();

#endif //HW8_TRICY_3D_ARRAY_H
