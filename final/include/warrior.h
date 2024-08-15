/*
 * Warrior.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include <iostream>
#include <vector>
#include <queue>

#include "./weapon.h"
#include "./my_logging.h"
/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_WARRIOR_H
#define FINAL_WARRIOR_H

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

        if ( W_init ) delete [] W_init;
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
        // it is alive and
        return !isDead() &&
               // it has weapons before the battle or it has weapons during the battle and
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

    void discardAllWeapons();

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


#endif //FINAL_WARRIOR_H
