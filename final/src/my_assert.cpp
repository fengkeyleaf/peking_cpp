/*
 * my_assert.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/22/2024
 */

#include "../include/my_assert.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

bool __M_Assert(
    const char *expr_str, bool expr, const char *file, int line, const char *msg
) {
    if ( !expr ) {
        std::cerr << "Assert failed message:\t" << msg << std::endl;
    }

    return expr;
}