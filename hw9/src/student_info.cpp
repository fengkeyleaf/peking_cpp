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


template<class T>
void Print( T first, T last ) {
    for ( ; first != last; ++first )
        std::cout << *first << ",";
    std::cout << std::endl;
}

void caller() {
    Student s[] = { { "Tom",   80 },
                    { "Jack",  70 },
                    { "Jone",  90 },
                    { "Tom",   70 },
                    { "Alice", 100 } };

    MyMultimap<std::string, int> mp;
    for ( int i = 0; i < 5; ++i )
        mp.insert( make_pair( s[ i ].name, s[ i ].score ) );
    Print( mp.begin(), mp.end() ); //按姓名从大到小输出

    mp.Set( "Tom", 78 ); //把所有名为"Tom"的学生的成绩都设置为78
    Print( mp.begin(), mp.end() );


    MyMultimap<int, std::string, std::less<int> > mp2;
    for ( int i = 0; i < 5; ++i )
        mp2.insert( make_pair( s[ i ].score, s[ i ].name ) );

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
            mp.insert( make_pair( name, score ) );
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

