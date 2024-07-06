/*
 * my_list_submit.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/6/2024
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

template<class T>
class MyVector {
    // https://en.cppreference.com/w/cpp/container/map
    std::map<size_t, std::vector<T>> M;

public:
    void append( size_t id, T& t_ );

    void add_new_list( size_t id_ );

    void merge( size_t id1, size_t id2 );

    void print( size_t id );

    void unique( size_t id );
};

template<class T>
void MyVector<T>::append( size_t id, T &t_ ) {
    if ( M.find( id ) == M.end() ) {
        std::cerr << "No such a list named " << id << std::endl;
        return;
    }

    M[ id ].push_back( t_ );
}

// https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
template<class T>
void MyVector<T>::unique( size_t id ) {
    if ( M.find( id ) == M.end() ) {
        std::cerr << "No such a list named " << id << std::endl;
        return;
    }

    std::set<T> S( M[ id ].begin(), M[ id ].end() );
    M[ id ].assign( S.begin(), S.end() );
}

template<class T>
void MyVector<T>::print( size_t id ) {
    if ( M.find( id ) == M.end() ) {
        std::cerr << "No such a list named " << id << std::endl;
        return;
    }

    std::sort( M[ id ].begin(), M[ id ].end() );
    for ( T& n : M[ id ] )
        std::cout << n << " ";

    std::cout << std::endl;
}

template<class T>
void MyVector<T>::merge( size_t id1, size_t id2 ) {
    if ( id1 == id2 ) return;

    if ( M.find( id1 ) == M.end() || M.find( id2 ) == M.end() ) {
        std::cerr << "No such a list named " << id1 << " or " << id2 << std::endl;
        return;
    }

    for ( T& t : M[ id2 ] ) M[ id1 ].push_back( t );
    M[ id2 ].clear();

    std::multiset<T> S( M[ id1 ].begin(), M[ id1 ].end() );
    M[ id1 ].assign( S.begin(), S.end() );
}

template<class T>
void MyVector<T>::add_new_list( size_t id_ ) {
    M[ id_ ];
}

void caller() {
    int n;
    std::cin >> n;

    MyVector<int> V;
    while ( n-- ) {
        size_t id;
        std::string s;
        std::cin >> s;
        if ( s == "new" ) {
            std::cin >> id;
            V.add_new_list( id );
        }
        else if ( s == "add" ) {
            std::cin >> id;
            int i;
            std::cin >> i;
            V.append( id, i );
        }
        else if ( s == "merge" ) {
            std::cin >> id;
            size_t id2;
            std::cin >> id2;
            V.merge( id, id2 );
        }
        else if ( s == "out" ) {
            std::cin >> id;
            V.print( id );
        }
        else if ( s == "unique" ) {
            std::cin >> id;
            V.unique( id );
        }
    }
}

int main() {

    caller();

    return 0;
}