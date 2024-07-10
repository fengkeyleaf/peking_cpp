/*
 * wow_war.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/10/2024
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <queue>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_WOW_WAR_H
#define FINAL_WOW_WAR_H

#define WARRIOR_NUM 5
#define WEAPON_NUM 3

// -------------------------------------------------------
// enum types
// -------------------------------------------------------

enum Color_enum {
    red,
    blue
};

enum Warrior_enum {
    dragon, // = 0
    ninja, // = 1
    iceman, // = 2
    lion, // = 3
    wolf // = 4
};

enum Weapon_enum {
    sword, // 0
    bomb, // 1
    arrow // 2
};

// -------------------------------------------------------
// class definition
// -------------------------------------------------------

// -------------------------------------------------------
// Warrior class
// -------------------------------------------------------

// https://en.cppreference.com/w/cpp/language/abstract_class
class Warrior {
protected:
    const size_t id; // ID
    const Warrior_enum t; // Type
    const size_t m; // Life points.
    Weapon_enum* W_ids = nullptr;

    Warrior( size_t id_, Warrior_enum t_, size_t m_ ) : id( id_ ), t( t_ ), m( m_ ) {}

    ~Warrior() { if ( W_ids ) delete [] W_ids; }

public:
    virtual void print() = 0;

    virtual bool escape( const char* t, const char* c ) { return false; };

    virtual void move() = 0;

    virtual void rob() = 0;

    virtual void attack( Warrior* e ) = 0;

    virtual bool isAttack() = 0;
};

class Dragon: public Warrior {
    const static char* OUT_FORMAT;
    double morale;

public:
    Dragon( size_t m_, size_t n_, size_t m_remained )
        : Warrior( dragon, m_ ), morale( ( double ) m_remained / m_ ) {
        W_ids = new Weapon_enum[ 1 ];
        W_ids[ 0 ] = static_cast<Weapon_enum>( n_ % WEAPON_NUM );
    }

    void print() override;
};

class Ninjia: public Warrior {
    const static char* OUT_FORMAT;

public:
    Ninjia( size_t m_, size_t n_ ) : Warrior( ninja, m_ ) {
        W_ids = new Weapon_enum[ 2 ];
        W_ids[ 0 ] = static_cast<Weapon_enum>( n_ % WEAPON_NUM );
        W_ids[ 1 ] = static_cast<Weapon_enum>( ( n_ + 1 ) % WEAPON_NUM );
    }

    void print() override;
};

class Iceman: public Warrior {
    const static char* OUT_FORMAT;

public:
    Iceman( size_t m_, size_t n_ ) : Warrior( iceman, m_ ) {
        W_ids = new Weapon_enum[ 1 ];
        W_ids[ 0 ] = static_cast<Weapon_enum>( n_ % WEAPON_NUM );
    }

    void print() override;
};

class Lion: public Warrior {
    const static char* OUT_FORMAT;
    const size_t k;
    int loyalty;

public:
    Lion( size_t m_, size_t m_remained, size_t k_ ) : Warrior( lion, m_ ), loyalty( m_remained ), k( k_ ) {}

    void print() override;

    bool escape( const char* t, const char* c ) override;
};

class Wolf: public Warrior {

public:
    Wolf( size_t m_ ) : Warrior( wolf, m_ ) {}

    void print() override;
};

// -------------------------------------------------------
// Game class
// -------------------------------------------------------

class Commander {
    const static std::string WARRIOR_NAMES[ WARRIOR_NUM ]; // global warrior names
    const static char* OUTPUT_FORMAT;

    const Color_enum c; // color
    int m; // total life points
    size_t k; // loyalty consumption points.
    const int* W_n; // local warrior names
    const size_t* M; // Warrior life points
    const size_t* P; // Warrior power points
    size_t n = 0; // warrior total count
    size_t C[ WARRIOR_NUM ] = { 0 }; // warrior count
    int idx = -1; // warrior index
    bool is_stopped = false;

    /**
     * Generate a warrior, but only print out its info for this assignment.
     *
     * @param t_ Warrior enum type.
     * @param warrior_m_ Warrior life point.
     * @param n_ Number id.
     * @param m_ Remained life points.
     * */

    Warrior* get_warrior( Warrior_enum t_, size_t warrior_m_, size_t n_, int m_ );

public:
    Commander( Color_enum c, const int *W ) : c( c ), W_n( W ) {}

    /**
     * Can this commander generate next warrior?
     *
     * @return An index to that warrior is returned if it can, otherwise -1 is returned.
     * */

    int hasNext();

    /**
     * Generate a warrior if this commander can do it.
     *
     * @param t Timestamp string in the format of "XXX"
     * */

    Warrior* generate( std::string &t );

    /**
     * Initialize resources.
     *
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void initResource( int m, size_t k, const size_t *M, const size_t *P );

    void report();
};

class City {
    bool isOdd = false;
    Warrior* r = nullptr; // red warrior
    Warrior* b = nullptr; // blue warrior

public:
    City( bool isOdd_ ) : isOdd( isOdd_ ) {}

    void lionEscaping();

    void moveForward();

    void wolfRobbing();

    void startBattle();
};

class WorldOfWarcraft {
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    size_t n = 0; // Number of cities
    size_t c = 0; // timestamp count
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE ); // blue headquarter
    City** C; // City list

    static std::string getTimeStr( size_t c );

    bool hasTime( size_t t );

    void lionEscaping( int t );

    void moveForward( int t, Warrior* r, Warrior* b );

    void wolfRobbing( int t );

    void startBattle( int t );

    void report( int t );

public:
    ~WorldOfWarcraft() {
        for ( size_t i = 0; i < n; i++ ) {
            delete C[ i ];
        }

        delete [] C;
    }

    /**
     * Start the game.
     *
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void start( size_t m_, size_t n_, size_t k_, size_t t_, const size_t* M_, const size_t* P_ );
};

void caller();

#endif //FINAL_WOW_WAR_H
