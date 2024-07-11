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
#include <cmath>

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

class Weapon;
class Warrior;

// -------------------------------------------------------
// Weapon class
// -------------------------------------------------------

class Weapon {
protected:
    const Weapon_enum t; // id
    int durability; // -1 no durability, 0 broken, >= 1 normal.
    size_t damage;

public:
    Weapon() : t( sword ), damage( 0 ) {}

    Weapon( Weapon_enum t_, size_t da_, size_t dur_ ) : t( t_ ), damage( da_ ), durability( dur_ ) {}

    Weapon_enum get_type() const;

    // https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c
    bool operator()( const Weapon* w1, const Weapon* w2 ) const;

    bool hasDurability() const;

    void consume();

    size_t get_damage() { return damage; }
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
    size_t m; // Life points.
    size_t m_pre; // previous life points.
    // https://www.geeksforgeeks.org/pointer-array-array-pointer/
    Weapon* (*W_init) = nullptr; // Initialized weapons.
    // https://en.cppreference.com/w/cpp/container/priority_queue
    std::priority_queue<Weapon*, std::vector<Weapon*>, Weapon> W_lib; // Weapon library.
    // https://en.cppreference.com/w/cpp/container/queue
    std::queue<Weapon*> W_remained; // Remained weapons
    Weapon* w_pre = nullptr; // Used weapon previously

    Warrior( size_t id_, Warrior_enum t_, size_t p_, size_t m_ )
    : id( id_ ), t( t_ ), p( p_ ), m( m_ ), m_pre( m_ ) {}

    Weapon* get_weapon( Weapon_enum t_, size_t p_ );

public:
    const size_t id; // ID
    const Warrior_enum t; // Type
    const size_t p; // power

    virtual ~Warrior() {
        delete [] W_init;
    }

    virtual void print() = 0;

    virtual bool escape( const char* t, const char* c ) { return false; };

    virtual void yell( const char* t, const char* c, size_t id_w, size_t id_c ) {}

    virtual void move() {}

    void rob( Warrior* e ) {
        while ( W_lib.size() < 10 && e->hasWeapons() ) {
            W_lib.push( e->getWeapon() );
        }
    }

    virtual void attacked( Weapon *w, Warrior* e, bool isSelf );

    void attack( Warrior* e );

    bool isDead() const { return m <= 0; }

    bool isChange() const {
        // life point changes or
        return m != m_pre ||
            // previously used weapon is bomb or arrow
            ( w_pre != nullptr && ( w_pre->get_type() == bomb || w_pre->get_type() == arrow ) );
    }

    bool canAttack() const {
        return !isDead() && !W_lib.empty() && !W_remained.empty() && isChange();
    }

    bool hasWeapons() const { return !W_lib.empty(); }

    Weapon* getWeapon() {
        assert( !W_lib.empty() );

        Weapon* w = W_lib.top();
        W_lib.pop();
        return w;
    }
};

class Dragon: public Warrior {
    const static char* OUT_FORMAT;
    double morale;

public:
    ~Dragon() {
        delete W_init[ 0 ];
    }

    Dragon( size_t id_, size_t m_, size_t p_, size_t n_, size_t m_remained )
    : Warrior( id_, dragon, p_, m_ ), morale( ( double ) m_remained / m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % 3 ), p_ );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;

    void yell( const char* t, const char* c, size_t id_w, size_t id_c ) override;
};

class Ninjia: public Warrior {
    const static char* OUT_FORMAT;

public:
    ~Ninjia() {
        delete W_init[ 0 ];
        delete W_init[ 1 ];
    }

    Ninjia( size_t id_, size_t m_, size_t p_, size_t n_ )
    : Warrior( id_, ninja, p_, m_ ) {
        W_init = new Weapon*[ 2 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ), p_ );
        W_init[ 1 ] = get_weapon( static_cast<Weapon_enum>( ( n_ + 1 ) % WEAPON_NUM ), p_ );
        W_lib.push( W_init[ 0 ] );
        W_lib.push( W_init[ 1 ] );
    }

    void print() override;

    void attacked( Weapon *w, Warrior* e, bool isSelf ) override;
};

class Iceman: public Warrior {
    const static char* OUT_FORMAT;

public:
    ~Iceman() {
        delete W_init[ 0 ];
    }

    Iceman( size_t id_, size_t m_, size_t p_, size_t n_ )
    : Warrior( id_, iceman, p_, m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ), p_ );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;

    void move() override;
};

class Lion: public Warrior {
    const static char* OUT_FORMAT;
    const size_t k;
    size_t loyalty;

public:
    ~Lion() {
        delete W_init[ 0 ];
    }

    Lion( size_t id_, size_t m_, size_t p_, size_t n_, size_t m_remained, size_t k_ )
    : Warrior( id_, lion, p_, m_ ), k( k_ ), loyalty( m_remained ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ), p_ );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;

    bool escape( const char* t, const char* c ) override;

    void move() override;
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
    const size_t id;
    const bool isOdd;
    Warrior* r = nullptr; // red warrior
    Warrior* b = nullptr; // blue warrior

public:
    City( size_t id_ ) : id( id_ ), isOdd( id_ % 2 != 0 ) {}

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
