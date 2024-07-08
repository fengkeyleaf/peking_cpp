/*
 * student_info.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/7/2024
 */

#include "../include/student_info.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// --------------------------------------------------
// class MyMultimap
// --------------------------------------------------

template<class Key, class T, class Compare>
void MyMultimap<Key, T, Compare>::insert( std::pair<Key, T> p ) {
    M.insert( p );
}

template<class Key, class T, class Compare>
void MyMultimap<Key, T, Compare>::Set( Key k, T v ) {
   auto r = M.equal_range( k );
   for ( auto i = r.first; i != r.second; i++ ) {
       i->second = v;
   }
}

template<class Key, class T, class Compare>
void MyMultimap<Key, T, Compare>::clear() {
    M.clear();
}

template<class Key, class T, class Compare>
typename MyMultimap<Key, T, Compare>::iterator MyMultimap<Key, T, Compare>::begin() {
    return MyMultimap<Key, T, Compare>::iterator( M.begin() );
}

template<class Key, class T, class Compare>
typename MyMultimap<Key, T, Compare>::iterator MyMultimap<Key, T, Compare>::end() {
    return MyMultimap<Key, T, Compare>::iterator( M.end() );
}

template<class Key, class T, class Compare>
typename MyMultimap<Key, T, Compare>::iterator MyMultimap<Key, T, Compare>::find( const Key &k ) {
    return MyMultimap<Key, T, Compare>::iterator( M.find( k ) );
}

// --------------------------------------------------
// class MyMultimap::iterator
// --------------------------------------------------

template<class Key, class T, class Compare>
bool MyMultimap<Key, T, Compare>::iterator::operator!=( const MyMultimap::iterator &iter_ ) {
    return iter != iter_.iter;
}

template<class Key, class T, class Compare>
typename std::multimap<Key, T, Compare>::iterator MyMultimap<Key, T, Compare>::iterator::operator->() {
    return iter;
}

template<class Key, class T, class Compare>
typename MyMultimap<Key, T, Compare>::iterator& MyMultimap<Key, T, Compare>::iterator::operator++() {
    ++iter;
    return *this;
}

template<class Key, class T, class Compare>
std::string MyMultimap<Key, T, Compare>::iterator::operator*() {
    std::cout << "(" << iter->first << "," << iter->second << ")";
    return std::string( "" );
}

// --------------------------------------------------
// Helper function
// --------------------------------------------------

template<class T>
void Print( T first, T last ) {
    for ( ; first != last; ++first )
        std::cout << *first << ",";
    std::cout << std::endl;
}

void caller() {
    // Debugging setting
//    std::ifstream fi( "/home/sora/perking_cpp/hw9/in_stu_info.txt" );
//    std::cin.rdbuf( fi.rdbuf() );
//    std::ofstream fo = std::ofstream( "/home/sora/perking_cpp/hw9/out_stu_info_test.txt" );
//    std::cout.rdbuf( fo.rdbuf() );

    Student s[] = { { "Tom",   80 },
                    { "Jack",  70 },
                    { "Jone",  90 },
                    { "Tom",   70 },
                    { "Alice", 100 } };

    MyMultimap<std::string, int> mp;
    for ( int i = 0; i < 5; ++i )
        mp.insert( std::make_pair( s[ i ].name, s[ i ].score ) );
    Print( mp.begin(), mp.end() ); //按姓名从大到小输出

    mp.Set( "Tom", 78 ); //把所有名为"Tom"的学生的成绩都设置为78
    Print( mp.begin(), mp.end() );


    MyMultimap<int, std::string, std::less<int> > mp2;
    for ( int i = 0; i < 5; ++i )
        mp2.insert( std::make_pair( s[ i ].score, s[ i ].name ) );

    Print( mp2.begin(), mp2.end() ); //按成绩从小到大输出
    mp2.Set( 70, "Error" );          //把所有成绩为70的学生，名字都改为"Error"
    Print( mp2.begin(), mp2.end() );
    std::cout << "******" << std::endl;

    mp.clear();

    std::string name;
    std::string cmd;
    int score;
    while ( std::cin >> cmd ) {
        if ( cmd == "A" ) {
            std::cin >> name >> score;
            if ( mp.find( name ) != mp.end() ) {
                std::cout << "erroe" << std::endl;
            }
            mp.insert( std::make_pair( name, score ) );
        } else if ( cmd == "Q" ) {
            std::cin >> name;
            MyMultimap<std::string, int>::iterator p = mp.find( name );
            if ( p != mp.end() ) {
                std::cout << p->second << std::endl;
            } else {
                std::cout << "Not Found" << std::endl;
            }
        }
    }
}
