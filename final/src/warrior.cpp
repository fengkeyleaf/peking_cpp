/*
 * Warrior.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "../include/warrior.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// -------------------------------------------------------
// Warrior class
// -------------------------------------------------------

Weapon* Warrior::getWeapon( Weapon_enum t_ ) {
    switch ( t_ ) {
        case sword:
            return new Sword();
        case bomb:
            return new Bomb();
        case arrow:
            return new Arrow();
        default:
            assert( false );
            return nullptr;
    }
}

void Warrior::organizeWeapons() {
    // Put all weapons from W_remained to W_lib,
    // which is necessary after a battle.
    while ( !W_remained.empty() ) {
        W_lib.push( W_remained.front() );
        W_remained.pop();
    }
}

void Warrior::attacked( Weapon* w, Warrior* e, bool isSelf ) {
    // ninjia can use a bomb without self-damage.
    if ( w->getType() == bomb && isSelf && t == ninja ) return;

    // Damage caused by this attack.
    size_t d = 0;
    // Self-damage caused by using a bomb
    if ( w->getType() == bomb && isSelf ) {
        d = std::floor( std::abs( ( double ) e->p - p ) * 1 / 10.0 );
        l.debug( stringFormat(
            "%s %ld got damage of %ld by using bomb\n",
            getName(), id, d
        ) );
    }
        // Damage caused by other weapons.
    else { d = w->getDamage( e->p ); }

    m_pre = m;
    // Calculate remained life points.
    if ( m <= d ) {
        m = 0;
        return;
    }

    m -= d;
}

void Warrior::attackLogging( Weapon* w, Warrior* e ) {
    l.debug( stringFormat(
        "%s %ld using %s with damage of %ld attacked %s %ld\n",
        getName(), id, w->getName(), w->getDamage( p ),
        e->getName(), e->id
    ) );
    l.debug( stringFormat(
        "%s %ld's m is %ld, and %s %ld's m is %ld\n",
        getName(), id, m,
        e->getName(), e->id, e->m
    ) );
    if ( w->isBroken() )
        l.debug( stringFormat(
            "%s is broken\n",
            w->getName()
        ) );
}

std::pair<Weapon_enum, size_t> Warrior::rob( Warrior *e, bool isBeforeBattle ) {
    // W_remained must be empty.
    assert( W_remained.empty() );

    size_t c = 0;
    Weapon* w_pre = nullptr;
    // Continue robbing iff the weapon library isn't full and the enemy has weapons.
    while ( W_lib.size() < 10 && e->hasWeapons() ) {
        // Get a weapon with the smallest id.
        Weapon* w_c = e->peekWeapon();
        // Stop robbing when this robbing action happening before a battle or
        // getting a weapon with a larger id.
        if ( isBeforeBattle || w_pre != nullptr && w_pre->getType() != w_c->getType() ) break;
        // The enemy drops it.
        e->dropWeapon();
        // Tis warrior holds it.
        W_lib.push( w_c );
        w_pre = w_c;
        c++;
    }

    return std::pair<Weapon_enum, size_t>( w_pre == nullptr ? sword : w_pre->getType(), c );
}

void Warrior::freeWeapon() {
    if ( w_pre == nullptr ) return;
    // Free up a weapon iff used one previously and

    // the weapon is arrow or bomb and it's broken.
    if ( ( w_pre->getType() == arrow || w_pre->getType() == bomb ) && w_pre->isBroken() ) {
        delete w_pre;
        w_pre = nullptr;
    }
}

void Warrior::attack( Warrior* e ) {
    assert( !isDead() );

    // First attack with weapons from the weapon library.
    if ( !W_lib.empty() ) {
        // Grab a weapon.
        Weapon* w = W_lib.top();
        // Free up memory for a used-up weapon like arrow or bomb.
        freeWeapon();
        // Record the weapon we're using.
        w_pre = w;
        // Attack the enemy.
        e->attacked( w, this, false );
        // Get damaged when using a bomb
        if ( w->getType() == bomb ) attacked( w, e, true );

        // Handling the weapon after attacking
        w->consume();
        W_lib.pop();
        // Push available weapons to W_remained for future use
        if ( !w->isBroken() ) W_remained.push( w );

        // logging
        attackLogging( w, e );
        return;
    }

    // Attack with remained weapons
    // Note that there are no bomb in W_remained,
    // so no self-damage here.
    if ( !W_remained.empty() ) {
        // Grab a weapon.
        Weapon* w = W_remained.front();
        // No bomb at this point.
        assert( w->getType() != bomb );
        // Free up memory for a used-up weapon like arrow.
        freeWeapon();
        w_pre = w;
        // Attack the enemy.
        e->attacked( w, this, false );
        w->consume();
        W_remained.pop();
        // Push it back to W_remained if it's not broken.
        if ( !w->isBroken() ) W_remained.push( w );

        // logging
        attackLogging( w, e );
    }
    // No weapons available, do nothing.

    // Delete the last broken weapon if necessary.
    freeWeapon();
}

void Warrior::organizeBeforeBattle() {
    m_pre = m;
}

void Warrior::organizeAfterBattle() {
    organizeWeapons();
    // Reset other variables.
    // Verify w_pre after a battle
    // w_pre is nullptr or
    assert( w_pre == nullptr ||
            // if w_pre is not null,
            // it is not a bomb b/c it should be deleted after one attacking action or
            w_pre->getType() != bomb ||
            // w_pre is an arrow, but it's not broken or
            w_pre->getType() == arrow && !w_pre->isBroken() ||
            // other cases that should be considered as being fine.
            true
    );
    w_pre = nullptr;
}

void Warrior::discardAllWeapons() {
    assert( W_remained.empty() );

    while( !W_lib.empty() ) {
        delete W_lib.top();
        W_lib.pop();
    }
}

// https://en.cppreference.com/w/cpp/utility/tuple
std::tuple<size_t, size_t, size_t> Warrior::countWeapons() {
    size_t c_s = 0; // sword number count
    size_t c_b = 0; // bomb number count
    size_t c_a = 0; // arrow number count

    // Assume all weapons are pushed into W_lib after a battle.
    while ( !W_lib.empty() ) {
        Weapon* w = W_lib.top();
        switch ( w->getType() ) {
            case sword:
                c_s++;
                break;
            case bomb:
                c_b++;
                break;
            case arrow:
                c_a++;
                break;
            default:
                assert( false );
        }

        W_lib.pop();
        W_remained.push( w );
    }

    // Put all weapons back to W_lib.
    organizeWeapons();
    // return the result.
    return { c_s, c_b, c_a };
}

void Warrior::report( const char* t, const char* c ) {
    assert( !isDead() );

    std::tuple<size_t, size_t, size_t> n = countWeapons();

    std::cout << stringFormat(
        "%s:55 %s %s %ld has %ld sword %ld bomb %ld arrow and %ld elements\n",
        t,
        c,
        getName(),
        id,
        std::get<0>( n ), // sword number
        std::get<1>( n ), // bomb number
        std::get<2>( n ), // arrow number
        m
    );
}

// Dragon ----------------------------------------------
const char* Dragon::OUT_FORMAT = "It has a %s,and its m is %ld, p is %ld\n";
std::string Dragon::print()  {
    std::string s = stringFormat(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->getType() ],
        m, p
    );
    return s;
}

void Dragon::yell( const char* t, const char* c, size_t id_w, size_t id_c ) {
    std::cout << stringFormat(
        "%s:40 %s dragon %ld yelled in city %ld\n",
        t, c, id_w, id_c
    );
}

// Ninjia ----------------------------------------------
const char* Ninjia::OUT_FORMAT = "It has a %s and a %s, and its m is %ld, p is %ld\n";
std::string Ninjia::print()  {
    std::string s = stringFormat(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->getType() ],
        WEAPON_NAMES[ W_init[ 1 ]->getType() ],
        m, p
    );
    return s;
}

// Iceman ----------------------------------------------
const char* Iceman::OUT_FORMAT = "It has a %s, and its m is %ld, p is %ld\n";
std::string Iceman::print() {
    std::string s = stringFormat(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->getType() ],
        m, p
    );
    return s;
}

// It's impossible that an iceman would die after moving forward.
// since life points don't change after they are less than 10.
void Iceman::move() {
    size_t d = std::floor( m * 1 / 10.0 );
    if ( m <= d ) {
        m = 0;
        return;
    }

    m -= d;
}

// Lion ----------------------------------------------
const char* Lion::OUT_FORMAT = "It's loyalty is %ld\n";
std::string Lion::print() {
    std::cout << stringFormat(
        OUT_FORMAT,
        loyalty
    );

    return stringFormat(
        "It has a %s, and its m is %ld, p is %ld\n",
        WEAPON_NAMES[ W_init[ 0 ]->getType() ],
        m, p
    );
}

bool Lion::escape( const char* t, const char* c ) {
    if ( loyalty > 0 ) return false;

    std::cout << stringFormat(
        "%s:05 %s lion %ld ran away\n",
        t, c, id
    );
    return true;
}

void Lion::move() {
    if ( loyalty <= k ) {
        loyalty = 0;
        return;
    }

    loyalty -= k;
}

// Wolf ----------------------------------------------

std::string Wolf::print() {
    return stringFormat(
        "its m is %ld, p is %ld\n",
        m, p
    );
}
