/*
 * coolblood_arena.h
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
#include <map>
#include <queue>
#include <iostream>
#include <cassert>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW9_COOLBLOOD_ARENA_H
#define HW9_COOLBLOOD_ARENA_H

class Game {
    const std::ofstream fo = std::ofstream( "/home/sora/perking_cpp/hw9/out_coldblood_test.txt" );

    // https://en.cppreference.com/w/cpp/container/set
    // https://en.cppreference.com/w/cpp/container/priority_queue
    std::map<size_t, std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>>> M_increasing;
    std::map<size_t, std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t>>, std::greater<size_t>> M_decreasing;

public:
    Game() {
        M_increasing[ 1000000000 ];
        M_increasing[ 1000000000 ].push( 1 );

        M_decreasing[ 1000000000 ];
        M_decreasing[ 1000000000 ].push( 1 );
    }

    // TODO: Follow-up: Do it in time complexity - O( logn ), space complexity - O( n ),
    //  currently, complexity - 4 * O( logn ), space complexity - O( 2n ),
    void add( size_t id, size_t p ) {
        _add( id, p );

        if ( M_increasing.find( p ) == M_increasing.end() ) M_increasing[ p ];
        if ( M_decreasing.find( p ) == M_decreasing.end() ) M_decreasing[ p ];

        M_increasing[ p ].push( id );
        M_decreasing[ p ].push( id );
    }

    void _add( size_t id, size_t p ) {
        // https://en.cppreference.com/w/cpp/container/set/upper_bound
        auto iter_in = M_increasing.lower_bound( p );
        auto iter_de = M_decreasing.lower_bound( p );

        if ( iter_de != M_decreasing.end() && iter_in != M_increasing.end() ) {
            size_t diff_in = std::abs( ( double ) iter_in->first - p );
            size_t diff_de = std::abs( ( double ) iter_de->first - p );

            // Same difference
            if ( diff_de == diff_in ) {
                size_t id_in = iter_in->second.top();
                size_t id_de = iter_de->second.top();

                // Compare id.
                std::cout << id << " " << ( id_in <= id_de ? id_in : id_de ) << std::endl;
            }
            else {
                std::cout << id << " " << ( diff_de <= diff_in ? iter_de->second.top() : iter_in->second.top() ) << std::endl;
            }
            return;
        }
        else if ( iter_de != M_decreasing.end() ) {
            std::cout << id << " " << iter_de->second.top() << std::endl;
            return;
        }
        else if ( iter_in != M_increasing.end() ) {
            std::cout << id << " " << iter_in->second.top() << std::endl;
            return;
        }

        assert( iter_in == M_increasing.end() && iter_de == M_decreasing.end() );
    }

    // https://unix.stackexchange.com/questions/45711/diff-reports-two-files-differ-although-they-are-the-same
    void redirect_to_file() {
        std::cout.rdbuf( fo.rdbuf() );
    }
};

void caller();

#endif //HW9_COOLBLOOD_ARENA_H
