/*
 * twoD_array.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 6/29/2024
 */

#include <iostream>
#include <cstring>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW4_TWOD_ARRAY_H
#define HW4_TWOD_ARRAY_H

// A better way to implement the class, but we cannot do it here since we are not allowed to add headers.
// Look into the following materials if you're interested:
// https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
// https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new/16239446#16239446
// https://www.geeksforgeeks.org/unique_ptr-in-cpp/
// https://www.geeksforgeeks.org/cpp-14-make_unique/
class Array2 {
    // https://stackoverflow.com/questions/19732319/difference-between-size-t-and-unsigned-int
    size_t r;
    size_t c;
    int *A;
public:
    Array2() {
        r = c = 0;
        A = nullptr;
    }

    Array2( size_t r, size_t c ) {
        this->r = r;
        this->c = c;
        A = new int[ r * c ];
    }

    // Unnecessary
    Array2( const Array2 &A ) {
        r = c = 0;
        this->A = nullptr;
    }

    ~Array2() {
        if ( A ) delete [] A;
    }

    int *operator[] ( size_t r ) {
        return r * c + A;
    }

    int &operator() ( size_t r, size_t c ) {
        return A[ r * this->c + c ];
    }

    Array2 &operator= ( const Array2 &A ) {
        if ( this->A ) delete [] this->A;

        c = A.c;
        r = A.r;
        size_t s = A.c * A.r;
        this->A = new int[ s ];
        std::copy( A.A, A.A + s, this->A );
        return *this;
    }
};

void caller();

#endif //HW4_TWOD_ARRAY_H
