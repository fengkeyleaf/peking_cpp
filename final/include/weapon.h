/*
 * Weapon.h
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
#include <cmath>

#include "./my_assert.h"
#include "./my_iostream.h"
#include "./config.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_WEAPON_H
#define FINAL_WEAPON_H

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

#endif //FINAL_WEAPON_H
