/*
 * wow_weapons.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/8/2024
 */

#include <iostream>
#include <string>
#include <queue>
#include <cassert>
#include <cmath>


/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef HW9_WOW_WEAPONS_H
#define HW9_WOW_WEAPONS_H

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
// Weapon class
// -------------------------------------------------------

class Weapon {
protected:
    const Weapon_enum t; // id
    const size_t damage;
    int durability; // -1 no durability, 0 broken, >= 1 normal.

public:
    Weapon( Weapon_enum t_, size_t da_, size_t dur_ ) : t( t_ ), damage( da_ ), durability( dur_ ) {}

    Weapon_enum get_type() const;
};

class Sword : public Weapon {
public:
    Sword( size_t p_ ) : Weapon( sword, std::floor( p_ * 2 / 10.0 ), -1 ) {}
};

class Bomb : public Weapon  {
public:
    Bomb( size_t p_ ) : Weapon( bomb, std::floor( p_ * 4 / 10.0 ), 1 ) {}
};

class Arrow : public Weapon {
public:
    Arrow( size_t p_ ) : Weapon( arrow, std::floor( p_ * 3 / 10.0 ), 2 ) {}
};

// -------------------------------------------------------
// Warrior class
// -------------------------------------------------------

// https://en.cppreference.com/w/cpp/language/abstract_class
class Warrior {
protected:
    const size_t id; // ID
    const Warrior_enum t; // Type
    const size_t p; // power
    size_t m; // Life points.
    // https://www.geeksforgeeks.org/pointer-array-array-pointer/
    Weapon* (*W_init) = nullptr; // Initialized weapons.
    std::priority_queue<Weapon*> W_lib; // Weapon library.

    Warrior( size_t id_, Warrior_enum t_, size_t p_, size_t m_ ) : id( id_ ), t( t_ ), p( p_ ), m( m_ ) {}

    Weapon* get_weapon( Weapon_enum t_, size_t p_ );

public:
    virtual ~Warrior() {
        delete [] W_init;

        while ( !W_lib.empty() ) {
            delete W_lib.top();
            W_lib.pop();
        }
    }

    virtual void print() = 0;
};

class Dragon: public Warrior {
    const static char* OUT_FORMAT;
    double morale;

public:
    Dragon( size_t id_, size_t m_, size_t p_, size_t n_, size_t m_remained )
    : Warrior( id_, dragon, p_, m_ ), morale( ( double ) m_remained / m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % 3 ), p_ );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;
};

class Ninjia: public Warrior {
    const static char* OUT_FORMAT;

public:
    Ninjia( size_t id_, size_t m_, size_t p_, size_t n_ )
    : Warrior( id_, ninja, p_, m_ ) {
        W_init = new Weapon*[ 2 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ), p_ );
        W_init[ 1 ] = get_weapon( static_cast<Weapon_enum>( ( n_ + 1 ) % WEAPON_NUM ), p_ );
        W_lib.push( W_init[ 0 ] );
        W_lib.push( W_init[ 1 ] );
    }

    void print() override;
};

class Iceman: public Warrior {
    const static char* OUT_FORMAT;

public:
    Iceman( size_t id_, size_t m_, size_t p_, size_t n_ )
    : Warrior( id_, iceman, p_, m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ), p_ );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;
};

class Lion: public Warrior {
    const static char* OUT_FORMAT;
    size_t loyalty;

public:
    Lion( size_t id_, size_t m_, size_t p_, size_t m_remained )
    : Warrior( id_, lion, p_, m_ ), loyalty( m_remained ) {}

    void print() override;
};

class Wolf: public Warrior {

public:
    Wolf( size_t id_, size_t m_, size_t p_ ) : Warrior( id_, wolf, p_, m_ ) {}

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
    const int *W_n; // local warrior names
    const size_t *M; // Warrior life points
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

    Warrior* get_warrior( size_t id_, Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_ );

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

    void generate( std::string &t );

    /**
     * Initialize resources.
     *
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void initResource( int m, const size_t *M );
};

class WorldOfWarcraft {
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    unsigned int c = 0; // timestamp count
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE ); // blue headquarter

    static std::string getTimeStr( size_t c );

public:
    /**
     * Start the game.
     *
     * @param n Case number.
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void start( size_t n, size_t m, const size_t *M );
};

void caller();

#endif //HW9_WOW_WEAPONS_H
