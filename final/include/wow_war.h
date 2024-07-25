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
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>
#include <fstream>
#include <cassert>
#include <memory>
#include <stdexcept>

#include "./my_logging.h"
#include "./my_assert.h"

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
#define MAX_CITY_NUM 20 // Excluding city 0 and city N + 1

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
    class Comparator {
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

    // -------------------------------------------------------
    // getter and setter
    // -------------------------------------------------------

    virtual size_t getDamage( size_t p_ ) = 0;

    const char* getName() const { return WEAPON_NAMES[ t ]; }
};

class Sword : public Weapon {
public:
    Sword() : Weapon( sword, -1 ) {}

    size_t getDamage( size_t p_ ) override;
};

class Bomb : public Weapon  {
public:
    Bomb() : Weapon( bomb, 1 ) {}

    size_t getDamage( size_t p_ ) override;
};

class Arrow : public Weapon {
public:
    Arrow() : Weapon( arrow, 2 ) {}

    size_t getDamage( size_t p_ ) override;
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
    // logging
    Logger& l;

    Warrior( size_t id_, Warrior_enum t_, size_t p_, size_t m_, Logger& l_ )
    : id( id_ ), t( t_ ), p( p_ ), m( m_ ), m_pre( m_ ), l( l_ ) {}

    /**
     * Get a weapon based on the type.
     * */

    static Weapon* getWeapon( Weapon_enum t_ );

    /**
     * Actions related to weapons.
     * */

    void organizeWeapons();

    /**
     * Being attacked by an enemy.
     *
     * @param w The weapon used to attack by the enemy.
     * @param e The enemy warrior.
     * @param isSelf Is this attack self-damaged?
     * */

    void attacked( Weapon *w, Warrior* e, bool isSelf );

    void attackLogging( Weapon*, Warrior* );

public:
    const size_t id; // ID, starting at 1.
    const Warrior_enum t; // Warrior type
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
     * @param e Enemy warrior.
     * @param isBeforeBattle Is this robbing action before a battle.
     * */

    std::pair<Weapon_enum, size_t> rob( Warrior* e, bool isBeforeBattle = false );

    /**
     * Free up the memory of a used weapon.
     * */

    void freeWeapon();


    /**
     * Attack an enemy.
     *
     * @param e The enemy warrior.
     * */

    void attack( Warrior* e );

    /**
     * Is this warrior dead?
     *
     * This warrior is dead iff its life points <= 0.
     * */

    bool isDead() const { return m <= 0; }

    /**
     * Does the status of this warrior change during a battle?
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

    /**
     * Actions before a battle finished.
     * */

    void organizeBeforeBattle();

    /**
     * Actions after a battle finished.
     * */

    void organizeAfterBattle();

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

    virtual std::string print() = 0;

    /**
     * Report after a battle.
     * */

    void report( const char* t, const char* c );
};

class Dragon: public Warrior {
    const static char* OUT_FORMAT;
    double morale;

public:
    Dragon( size_t m_, size_t p_, size_t n_, size_t m_remained, Logger& l_ )
    : Warrior( n_, dragon, p_, m_, l_ ), morale( ( double ) m_remained / m_ ) {
        // Default weapons.
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % 3 ) );
        // Push them into the weapon library.
        W_lib.push( W_init[ 0 ] );
    }

    std::string print() override;

    void yell( const char* t, const char* c, size_t id_w, size_t id_c ) override;
};

class Ninjia: public Warrior {
    const static char* OUT_FORMAT;

public:
    Ninjia( size_t m_, size_t p_, size_t n_, Logger& l_ )
    : Warrior( n_, ninja, p_, m_, l_ ) {
        W_init = new Weapon*[ 2 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ) );
        W_init[ 1 ] = getWeapon( static_cast<Weapon_enum>( ( n_ + 1 ) % WEAPON_NUM ) );
        W_lib.push( W_init[ 0 ] );
        W_lib.push( W_init[ 1 ] );
    }

    std::string print() override;
};

class Iceman: public Warrior {
    const static char* OUT_FORMAT;

public:
    Iceman( size_t m_, size_t p_, size_t n_, Logger& l_ )
    : Warrior( n_, iceman, p_, m_, l_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ) );
        W_lib.push( W_init[ 0 ] );
    }

    std::string print() override;

    void move() override;
};

class Lion: public Warrior {
    const static char* OUT_FORMAT;
    const size_t k;
    size_t loyalty;

public:
    Lion( size_t m_, size_t p_, size_t n_, size_t m_remained, size_t k_, Logger& l_ )
    : Warrior( n_, lion, p_, m_, l_ ), k( k_ ), loyalty( m_remained ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = getWeapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ) );
        W_lib.push( W_init[ 0 ] );
    }

    std::string print() override;

    bool escape( const char* t, const char* c ) override;

    void move() override;
};

class Wolf: public Warrior {

public:
    Wolf( size_t m_, size_t p_, size_t n_, Logger& l_ ) : Warrior( n_, wolf, p_, m_, l_ ) {}

    std::string print() override;
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
    // logging
    Logger& l;

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

    Commander( Color_enum c, const int *W, Logger& l_ ) : c( c ), W_n( W ), l( l_ ) {}

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

    void report( const char* t ) const;

    // -------------------------------------------------------
    // Setter and getter
    // -------------------------------------------------------

    void setOccupied() { is_occupied = true; }

    bool IsOccupied() const { return is_occupied; }
};

class City {
    const static char* MATCH_OUTPUT_FORMAT;
    const static char* ROB_OUTPUT_FORMAT;
    const static char* BATTLE_ONE_DEAD_OUTPUT_FORMAT;
    const static char* BATTLE_BOTH_DEAD_OUTPUT_FORMAT;
    const static char* BATTLE_BOTH_ALIVE_OUTPUT_FORMAT;
    const static char* OCCUPATION_OUTPUT_FORMAT;

    // Unique identity number, this may change for the city with the blue headquarters.
    size_t id; // Starting at 0.
    const bool isOdd;
    // https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const
    Commander* const c; // Commander or headquarter
    Warrior* r = nullptr; // red warrior
    Warrior* b = nullptr; // blue warrior
    std::queue<Warrior*>* Q; // Queue to store warriors arriving in a headquarters.
    // logging
    Logger& l;

public:
    City( size_t id_, Commander* c_, Logger& l_ ) : id( id_ ), isOdd( id_ % 2 != 0 ), c( c_ ), l( l_ ) {
        if ( c_ ) Q = new std::queue<Warrior*>;
    }

    ~City() {
        cleanUp();

        if ( Q ) delete Q;
    }

    void lionEscaping( const char* t_ );

    /**
     * Red warriors march forward.
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void moveForwardRed( City* c_, const char* t_ );

    /**
     * Blue warriors march forward.
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

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
     * Note that only invoke this method with cities having commanders.
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

    void cleanUp();

    // -------------------------------------------------------
    // Setter and getter
    // -------------------------------------------------------

    Commander* getCommander() { return c; }

    void setId( size_t id_ ) {
        assert( c != nullptr && c->c == blue );
        id = id_;
    }
};

class WorldOfWarcraft {
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    // logging
    Logger l;

    // Game data field.
    size_t c = 0; // timestamp count in hours
    size_t n = 0; // Number of cities
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED, l ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE, l ); // blue headquarter
    City** C; // City list from 0 to N + 1

    static std::string getTimeStr( size_t c );

    /**
     * Have enough time to go through next events?
     *
     * @param t Time period when we report the battlefield.
     * */

    bool hasTime( int t ) const;

    /**
     * Set up the game.
     *
     * @param n_ Number of cities excluding city 0 and N + 1.
     * */

    void setUp( size_t n_ );

    void cleanUp();

    /**
     * XXX:05 - Lion whose loyalty <= 0 escapes.
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void lionEscaping( int t_, const char* t_str );

    /**
     * XXX:10 - move one step forward
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void moveForward( int t, const char* t_str );

    /**
     * XXX:35 - Wolf robbing action
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void wolfRobbing( int t, const char* t_str );

    /**
     * XXX:40 - battle starts
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void startBattle( int t, const char* t_str );

    /**
     * XXX:50 - headquarters report remained life points
     * and
     * XXX:55 - Warriors report their owned weapons.
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    void report( int t, const char* t_str );

public:
    WorldOfWarcraft() : WorldOfWarcraft( WARNING ) {}

    WorldOfWarcraft( LogLevel ll ) : l( Logger( ll ) ) {
        // Initialize the city list
        C = new City*[ MAX_CITY_NUM + 2 ];
        for ( size_t i = 0; i < MAX_CITY_NUM + 2; i++ ) {
            if ( i == 0 ) C[ i ] = new City( i, &comm_red, l ); // city 0
            else if ( i == MAX_CITY_NUM + 1 ) C[ i ] = new City( i, &comm_blue, l ); // city N + 1
            else C[ i ] = new City( i, nullptr, l ); // cities in between
        }
    }

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

// -------------------------------------------------------
// Helper functions
// -------------------------------------------------------

void debugging();

// TODO: Put into a separate file, but have undefined reference error.
// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template<typename ... Args>
std::string stringFormat( const char* format, Args ... args );

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller();

#endif //FINAL_WOW_WAR_H
