/*
 * fun_and_do.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/fun_and_do.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// A &p
// A::Fun
//A::Do

// B &p
// A::Fun
// C::Do

// C &p
// C::Fun
// C::Do
void Call( B &p )  {
    p.Fun(); // A::Fun
    p.Do(); // C::Do
}

void caller() {
    C c;
    Call( c );
}