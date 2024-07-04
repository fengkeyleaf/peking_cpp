/*
 * fun_and_do_again.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/fun_and_do_again.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void Call( A *p ) {
    p->Fun();
    p->Do();
}

void caller() {
    // A::Fun
    // A::Do
    Call( new A() );
    // A::Fun
    // C::Do
    Call( new C() );
}