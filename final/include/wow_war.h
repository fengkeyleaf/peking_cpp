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
#include <queue>
#include <cmath>
#include <tuple>
#include <cassert>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_WOW_WAR_H
#define FINAL_WOW_WAR_H

// -------------------------------------------------------
// Marco
// -------------------------------------------------------

#define WARRIOR_NUM 5
#define WEAPON_NUM 3

// -------------------------------------------------------
// Global variables
// -------------------------------------------------------

extern const char *COLOR_NAMES[];
extern const char *WEAPON_NAMES[];
extern const std::string WARRIOR_NAMES[]; // global warrior names

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
    const Weapon_enum t; // Type id
    int durability; // -1 no durability, 0 broken, >= 1 normal.

public:
    static class Comparator {
    public:
        // https://stackoverflow.com/questions/23997104/priority-queue-with-pointers-and-comparator-c
        bool operator()( const Weapon* w1, const Weapon* w2 ) const;
    };

    Weapon( Weapon_enum t_, size_t dur_ ) : t( t_ ), durability( dur_ ) {}

    virtual ~Weapon() {}

    Weapon_enum getType() const;

    /**
     * Is this weapon broken.
     * */

    bool isBroken() const;

    void consume();

    virtual size_t get_damage( size_t p_ ) = 0;
};

class Sword : public Weapon {
public:
    Sword() : Weapon( sword, -1 ) {}

    size_t get_damage( size_t p_ ) override;
};

class Bomb : public Weapon  {
public:
    Bomb() : Weapon( bomb, 1 ) {}

    size_t get_damage( size_t p_ ) override;
};

class Arrow : public Weapon {
public:
    Arrow() : Weapon( arrow, 2 ) {}

    size_t get_damage( size_t p_ ) override;
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
    std::priority_queue<Weapon*, std::vector<Weapon*>, Weapon::Comparator> W_lib; // Weapon library.
    // https://en.cppreference.com/w/cpp/container/queue
    // Remained weapons library
    // Only used during a battle when using all weapons once in W_lib.
    std::queue<Weapon*> W_remained;
    Weapon* w_pre = nullptr; // Used weapon previously

    Warrior( size_t id_, Warrior_enum t_, size_t p_, size_t m_ )
    : id( id_ ), t( t_ ), p( p_ ), m( m_ ), m_pre( m_ ) {}

    Weapon* getWeapon( Weapon_enum t_ );

public:
    const size_t id; // ID
    const Warrior_enum t; // Type
    const size_t p; // power

    virtual ~Warrior() {
        assert( W_remained.empty() );

        // Free unused weapons
        while( !W_lib.empty() ) {
            delete W_lib.top();
            W_lib.pop();
        }

        delete [] W_init;
    }

    /**
     * Warrior whose loyalty <= 0 escapes.
     *
     * @param t Timestamp of hour string in the format of "XXX"
     * @param c Commander color string.
     * @return  To tell if this warrior escapes or not.
     * */

    virtual bool escape( const char* t, const char* c ) { return false; };

    /**
     * Yell after a battle.
     *
     * @param t Timestamp of hour string in the format of "XXX"
     * @param c Commander color string.
     * @param id_w Warrior id.
     * @param id_c City id.
     * */

    virtual void yell( const char* t, const char* c, size_t id_w, size_t id_c ) {}

    /**
     * The actions that this warrior may perform when moving forward.
     * */

    virtual void move() {}

    /**
     * Rob the enemy before or after a battle.
     *
     * @param isBeforeBattle Is this robbing action before a battle.
     * */

    std::pair<Weapon_enum, size_t> rob( Warrior* e, bool isBeforeBattle = false );

    /**
     * Attack an enemy.
     *
     * @param e The enemy warrior.
     * */

    void attack( Warrior* e );

    /**
     * Being attacked by an enemy.
     *
     * @param w The weapon used to attack by the enemy.
     * @param e The enemy warrior.
     * @param isSelf Is this attack self-damaged?
     * */

    void attacked( Weapon *w, Warrior* e, bool isSelf );

    /**
     * Is this warrior dead?
     *
     * This warrior is dead iff its life points <= 0.
     * */

    bool isDead() const { return m <= 0; }

    /**
     * Does the status of this warrior change?
     * */

    bool isChange() const {
        // Status change of life point.
        // life point changes or
        return m != m_pre ||
        // Status change of weapon.
        // previously used weapon is bomb or arrow
        ( w_pre != nullptr && ( w_pre->getType() == bomb || w_pre->getType() == arrow ) );
    }

    /**
     * Can this warrior fight?
     * */

    bool canAttack() const {
        // This warrior can fight iff
        // it is alive and i
        return !isDead() &&
        // t has weapons before the battle or it has weapons during the battle and
        ( !W_lib.empty() || !W_remained.empty() ) &&
        // its status changes.
        isChange();
    }

    // -------------------------------------------------------
    // Getter and setter
    // -------------------------------------------------------

    bool hasWeapons() const { return !W_lib.empty(); }

    Weapon* peekWeapon() {
        assert( !W_lib.empty() );

        Weapon* w = W_lib.top();
        return w;
    }

    void dropWeapon() {
        assert( !W_lib.empty() );

        W_lib.pop();
    }

    const char* getName() const {
       return WARRIOR_NAMES[ t ].c_str();
    }

    size_t getLifePoints() const {
        return m;
    }

    std::tuple<size_t, size_t, size_t> countWeapons();

    // -------------------------------------------------------
    // toString
    // -------------------------------------------------------

    /**
     * Print out the info of this warrior when it is generated.
     * */

    virtual void print() = 0;

    void report( const char* t, const char* c );
};

class Dragon: public Warrior {
    const static char* OUT_FORMAT;
    double morale;

public:
    ~Dragon() {
        delete W_init[ 0 ];
    }

    Dragon( size_t m_, size_t p_, size_t n_, size_t m_remained )
    : Warrior( n_, dragon, p_, m_ ), morale( ( double ) m_remained / m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % 3 ) );
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

    Ninjia( size_t m_, size_t p_, size_t n_ )
    : Warrior( n_, ninja, p_, m_ ) {
        W_init = new Weapon*[ 2 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ) );
        W_init[ 1 ] = getWeapon( static_cast<Weapon_enum>( ( n_ + 1 ) % WEAPON_NUM ) );
        W_lib.push( W_init[ 0 ] );
        W_lib.push( W_init[ 1 ] );
    }

    void print() override;
};

class Iceman: public Warrior {
    const static char* OUT_FORMAT;

public:
    ~Iceman() {
        delete W_init[ 0 ];
    }

    Iceman( size_t m_, size_t p_, size_t n_ )
    : Warrior( n_, iceman, p_, m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ) );
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

    Lion( size_t m_, size_t p_, size_t n_, size_t m_remained, size_t k_ )
    : Warrior( n_, lion, p_, m_ ), k( k_ ), loyalty( m_remained ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ) );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;

    bool escape( const char* t, const char* c ) override;

    void move() override;
};

class Wolf: public Warrior {

public:
    Wolf( size_t m_, size_t p_, size_t n_ ) : Warrior( n_, wolf, p_, m_ ) {}

    void print() override;
};

// -------------------------------------------------------
// Game class
// -------------------------------------------------------

class Commander {
    const static char* OUTPUT_FORMAT;

    int m; // total life points
    size_t k; // loyalty consumption points.
    const int* W_n; // local warrior names
    const size_t* M; // Warrior life points
    const size_t* P; // Warrior power points
    size_t n = 0; // warrior total count
    size_t C[ WARRIOR_NUM ] = { 0 }; // warrior count
    int idx = -1; // Warrior index. i.e. which warrior generated in last round.
    bool is_stopped = false; // Is stopping generating warriors? i.e. normal termination without occupation
    bool is_occupied = false;

    /**
     * Generate a warrior, but only print out its info for this assignment.
     *
     * @param t_ Warrior enum type.
     * @param warrior_m_ Warrior life point.
     * @param p_ Warrior power point.
     * @param n_ Warrior number id.
     * @param m_ Remained life points of the commander.
     * */

    Warrior* getWarrior( Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_ ) const;

public:
    const Color_enum c; // color

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

    Warrior* generate( const char* t );

    /**
     * Initialize resources.
     *
     * @param m_ Total life points.
     * @param k_ Loyalty consumption points
     * @param M_ Array to indicate life points to generate a warrior.
     * @param P_ Array to indicate power points of a warrior.
     * */

    void initResource( int m_, size_t k_, const size_t* M_, const size_t* P_ );

    void report( const char* t );

    void setOccupied() { is_occupied = true; }
};

class City {
    const static char* MATCH_OUTPUT_FORMAT;
    const static char* ROB_OUTPUT_FORMAT;
    const static char* BATTLE_ONE_DEAD_OUTPUT_FORMAT;
    const static char* BATTLE_BOTH_DEAD_OUTPUT_FORMAT;
    const static char* BATTLE_BOTH_ALIVE_OUTPUT_FORMAT;
    const static char* OCCUPATION_OUTPUT_FORMAT;

    const size_t id;
    const bool isOdd;
    // https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const
    Commander* const c; // Commander or headquarter
    Warrior* r = nullptr; // red warrior
    Warrior* b = nullptr; // blue warrior
    std::queue<Warrior*>* Q; // Queue to store warriors arriving in a headquarters.

public:
    City( size_t id_, Commander* c_ ) : id( id_ ), isOdd( id_ % 2 != 0 ), c( c_ ) {
        if ( c_ ) Q = new std::queue<Warrior*>;
    }

    ~City() {
        // Free resources for the warriors in this city.
        if ( r ) delete r;
        if ( b ) delete b;

        // Free resources for the warriors arriving the headquarters.
        while ( Q != nullptr && !Q->empty() ) {
            delete Q->front();
            Q->pop();
        }
        if ( Q ) delete Q;
    }

    void lionEscaping( const char* t_ );

    void moveForwardRed( City* c_, const char* t_ );

    void moveForwardBlue( City* c_, const char* t_ );

    void wolfRobbing( const char* t );

    /**
     * Start battle in this city.
     *
     * @param t Timestamp string in the format of "XXX"
     * */

    void startBattle( const char* t );

    /**
     * Add a warrior to this city.
     *
     * @param w A warrior to be added.
     * */

    void addWarrior( Warrior* w );

    /**
     * Notify that this headquarters has been occupied.
     *
     * @param t Timestamp string in the format of "XXX"
     * */

    void notifyOccupied( const char* t );

    /**
     * Report after a battle.
     *
     * @param t Timestamp string in the format of "XXX"
     * */

    void report( const char* t );
};

class WorldOfWarcraft {
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    size_t c = 0; // timestamp count
    size_t n = 0; // Number of cities
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE ); // blue headquarter
    City** C; // City list from 0 to N + 1

    static std::string getTimeStr( size_t c );

    /**
     * Have enough time to go through next events?
     *
     * @param t Time period when we report the battlefield.
     * */

    bool hasTime( int t ) const;

    /**
     * XXX:05 - Lion whose loyalty <= 0 escapes.
     * */

    void lionEscaping( int t_, const char* t_str );

    /**
     * XXX:10 - move one step forward
     * */

    void moveForward( int t, const char* t_str  );

    /**
     * XXX:35 - Wolf robbing action
     * */

    void wolfRobbing( int t, const char* t_str );

    /**
     * XXX:40 - battle starts
     * */

    void startBattle( int t, const char* t_str );

    /**
     * XXX:50 - headquarters report remained life points
     * and
     * XXX:55 - Warriors report their owned weapons.
     *
     * */

    void report( int t, const char* t_str );

public:
    ~WorldOfWarcraft() {
        for ( size_t i = 0; i < n + 2; i++ ) {
            delete C[ i ];
        }

        delete [] C;
    }

    /**
     * Start the game.
     *
     * @param m_ Total life points.
     * @param n_ Number of cities.
     * @param k_ Loyalty consumption points
     * @param t_ Time period when we report the battlefield.
     * @param M_ Array to indicate life points to generate a warrior.
     * @param P_ Array to indicate power points of a warrior.
     * */

    void start( size_t m_, size_t n_, size_t k_, int t_, const size_t* M_, const size_t* P_ );
};

void caller();

#endif //FINAL_WOW_WAR_H
