/*
 * Weapon.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "../include/weapon.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// -------------------------------------------------------
// Weapon class
// -------------------------------------------------------

// https://en.cppreference.com/w/cpp/container/priority_queue
// Note that the Compare parameter is defined such that it returns true if its first argument comes
// before its second argument in a weak ordering.
// But because the priority queue outputs largest elements first,
// the elements that "come before" are actually output last.
// That is, the front of the queue contains the "last" element according to the weak ordering imposed by Compare.
bool Weapon::Comparator::operator()( const Weapon *w1, const Weapon *w2 ) const {
    // TODO: Not necessary must be arrow.
    if ( w1->t == w2->t && w1->t == arrow ) {
        return w1->durability >= w2->durability;
    }

    return w1->t >= w2->t;
}

Weapon_enum Weapon::getType() const {
    return t;
}

bool Weapon::isBroken() const {
    return durability == 0;
}

void Weapon::consume() {
    assert( M_Assert(
        durability != 0,
        stringFormat( "type=%s, dur=%d", WEAPON_NAMES[ t ], durability ).c_str()
    ) );

    // Avoid overflow.
    if ( durability < 0 ) return;

    durability--;
}

size_t Sword::getDamage( size_t p_ ) {
    return std::floor( p_ * 2 / 10.0 );
}

size_t Bomb::getDamage( size_t p_ ) {
    return std::floor( p_ * 4 / 10.0 );
}

size_t Arrow::getDamage( size_t p_ ) {
    return std::floor( p_ * 3 / 10.0 );
}