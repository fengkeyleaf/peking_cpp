/*
 * arena.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/7/2024
 */

#include <fstream>
#include <set>
#include <iostream>
#include <cassert>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW9_ARENA_H
#define HW9_ARENA_H


class Game {
    const std::ofstream fo = std::ofstream( "/home/sora/perking_cpp/hw9/out_arena_test.txt" );

    // https://en.cppreference.com/w/cpp/container/set
    std::set<std::pair<size_t, size_t>> M_increasing;
    std::set<std::pair<size_t, size_t>, std::greater<std::pair<size_t, size_t>>> M_decreasing;

public:
    Game() {
        M_increasing.insert( std::pair<size_t, size_t>( 1000000000, 1 ) );
        M_decreasing.insert( std::pair<size_t, size_t>( 1000000000, 1 ) );
    }

     // TODO: Follow-up: Do it in time complexity - O( logn ), space complexity - O( n ),
     //  currently, complexity - 4 * O( logn ), space complexity - O( 2n ),
    void add( size_t id, size_t p ) {
        std::pair<size_t, size_t> pair ( p, id );
        M_increasing.insert( pair );
        M_decreasing.insert( pair );

        // https://en.cppreference.com/w/cpp/container/set/upper_bound
        std::set<std::pair<size_t, size_t>>::iterator iter_in = M_increasing.upper_bound( pair );
        std::set<std::pair<size_t, size_t>>::iterator iter_de = M_decreasing.upper_bound( pair );

        if ( iter_de != M_decreasing.end() && iter_in != M_increasing.end() ) {
            size_t diff_in = std::abs( ( double ) iter_in->first - p );
            size_t diff_de = std::abs( ( double ) iter_de->first - p );

            std::cout << id << " " << ( diff_de <= diff_in ? iter_de->second : iter_in->second ) << std::endl;
            return;
        }
        else if ( iter_de != M_decreasing.end() ) {
            std::cout << id << " " << iter_de->second << std::endl;
            return;
        }
        else if ( iter_in != M_increasing.end() ) {
            std::cout << id << " " << iter_in->second << std::endl;
            return;
        }

        assert( iter_in == M_increasing.end() && iter_de == M_decreasing.end() );
    }

    void redirect_to_file() {
        std::cout.rdbuf( fo.rdbuf() );
    }
};

void caller();

#endif //HW9_ARENA_H
