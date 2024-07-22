/*
 * my_assert.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/22/2024
 */

#include <iostream>
#include <cassert>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_MY_ASSERT_H
#define FINAL_MY_ASSERT_H

// https://stackoverflow.com/questions/3692954/add-custom-messages-in-assert
// M_Assert(ptr != nullptr, "MyFunction: requires non-null argument");
#ifndef NDEBUG
#   define M_Assert( Expr, Msg ) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_Assert(Expr, Msg) ;
#endif

bool __M_Assert( const char *expr_str, bool expr, const char *file, int line, const char *msg );

#endif //FINAL_MY_ASSERT_H
