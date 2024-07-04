/*
 * looks_like_polymorphism.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/4/2024
 */

#include "../include/looks_like_polymorphism.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void caller() {
    B *pb;
    D *pd;
    D d( 4 );
    d.Fun(); // D::Fun
    pb = new B( 2 );
    pd = new D( 8 );
    pb->Fun(); // B::Fun
    pd->Fun(); // D::Fun
    pb->Print(); // nBVal=2
    pd->Print(); // nBVal=24 // nDVal=8

    delete pb;

    pb = &d;
    pb->Fun(); // B::Fun
    pb->Print(); // nBVal=12

    delete pd;
}