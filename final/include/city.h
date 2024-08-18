/*
 * city.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "./warrior.h"
#include "./commander.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_CITY_H
#define FINAL_CITY_H

class City {
    // Output string format.
    const static char* MATCH_OUTPUT_FORMAT;
    const static char* MATCH_OUTPUT_HEADQUARTER_FORMAT;
    const static char* ROB_OUTPUT_FORMAT;
    const static char* BATTLE_ONE_DEAD_OUTPUT_FORMAT;
    const static char* BATTLE_BOTH_DEAD_OUTPUT_FORMAT;
    const static char* BATTLE_BOTH_ALIVE_OUTPUT_FORMAT;
    const static char* OCCUPATION_OUTPUT_FORMAT;

    // Unique identity number, this may change for the city with the blue headquarters.
    size_t id; // Starting at 0.
    // Attacking order
    const bool isOdd;
    bool isToggleAttackingOrder = false;
    // https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const
    Commander* const c; // Commander or headquarter
    Warrior* r = nullptr; // red warrior
    Warrior* b = nullptr; // blue warrior
    std::queue<Warrior*>* Q = nullptr; // Queue to store warriors arriving in a headquarters.
    // logging
    Logger& l;

    /**
     * Can go on next round?
     * */

    bool canAttack();

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
     * Red warriors march forward, from this city to c_
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    std::string moveForwardRed( City* c_, const char* t_ );

    /**
     * Blue warriors march forward, from this city to c_
     *
     * @param t Time period when we report the battlefield.
     * @param t_str Timestamp in hours string in the format of "XXX"
     * */

    std::string moveForwardBlue( City* c_, const char* t_ );

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

    std::string notifyOccupied( const char* t );

    /**
     * Report after a battle.
     *
     * @param t Timestamp string in the format of "XXX"
     * */

    void report( const char* t );

    /**
     * Clean up resources after the game.
     * */

    void cleanUp();

    // -------------------------------------------------------
    // Setter and getter
    // -------------------------------------------------------

    Commander* getCommander() { return c; }

    void setId( size_t id_ ) {
        assert( c != nullptr && c->c == blue );
        id = id_;
    }

    void setRedWarrior( Warrior* w ) {
        assert( r == nullptr );
        r = w;
    }

    Warrior* getRedWarrior() { return r; }

    void setBlueWarrior( Warrior* w ) {
        assert( b == nullptr );
        b = w;
    }

    Warrior* getBlueWarrior() { return b; }

    void setToggleAttackingOrder( bool t ) {
        isToggleAttackingOrder = t;
    }

    /**
     * Is this city occupied?
     *
     * Note that only a city with a commander can be occupied.
     * */

    bool isOccupied() const {
        assert( c != nullptr );

        return c->isOccupied();
    };
};


#endif //FINAL_CITY_H
