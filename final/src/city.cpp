/*
 * city.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "../include/city.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// -------------------------------------------------------
// class City
// -------------------------------------------------------

const char* City::MATCH_OUTPUT_FORMAT = "%s:10 %s %s %ld marched to city %ld with %ld elements and force %ld\n";
const char* City::MATCH_OUTPUT_HEADQUARTER_FORMAT = "%s:10 %s %s %ld reached %s headquarter with %ld elements and force %ld\n";
const char* City::ROB_OUTPUT_FORMAT = "%s:35 %s %s %ld took %ld %s from %s %s %ld in city %ld\n";
const char* City::BATTLE_ONE_DEAD_OUTPUT_FORMAT = "%s:40 %s %s %ld killed %s %s %ld in city %ld remaining %ld elements\n";
const char* City::BATTLE_BOTH_DEAD_OUTPUT_FORMAT = "%s:40 both %s %s %ld and %s %s %ld died in city %ld\n";
const char* City::BATTLE_BOTH_ALIVE_OUTPUT_FORMAT = "%s:40 both %s %s %ld and %s %s %ld were alive in city %ld\n";
const char* City::OCCUPATION_OUTPUT_FORMAT = "%s:10 %s headquarter was taken\n";

bool City::canAttack() {
    assert( r != nullptr && b != nullptr );

//    l.debug( stringFormat(
//        "%d, %d, %d, %d\n",
//        r->isDead(), b->isDead(),
//        r->isChange(), b->isChange()
//     ) );
    // Can go on next round iff
    // both warriors are alive and
    return ( !r->isDead() && !b->isDead() ) &&
        // One of their statuses has changed.
        ( r->isChange() || b->isChange() );
}

void City::lionEscaping( const char* t_ ) {
    // Has a red warrior in this city?
    if ( r ) {
        // Yes, does the warrior escape?
        if ( r->escape( t_, COLOR_NAMES[ red ] ) ) {
            // Yes, free the allocated resource.
            delete r;
            r = nullptr;
        }
    }

    if ( b ) {
        if ( b->escape( t_, COLOR_NAMES[ blue ] ) ) {
            delete b;
            b = nullptr;
        }
    }
}

std::string City::moveForwardRed( City* c_, const char* t_ ) {
    if ( r == nullptr ) return "";
    assert( c_->r == nullptr );

    // Move the red warrior from i to i + 1;
    c_->r = r;
    // The actions that the red warrior may perform when moving forward.
    r->move();
    // Output marching info.
    std::string s;
    // if city i + 1 is the blue headquarters,
    // notify that it has been occupied.
    if ( c_->c != nullptr ) {
        s = stringFormat(
            MATCH_OUTPUT_HEADQUARTER_FORMAT,
            t_,
            COLOR_NAMES[ red ],
            r->getName(),
            r->id,
            COLOR_NAMES[ blue ],
            r->getLifePoints(),
            r->p
        );
        s += c_->notifyOccupied( t_ );
    } else {
        s = stringFormat(
            MATCH_OUTPUT_FORMAT,
            t_,
            COLOR_NAMES[ red ],
            r->getName(),
            r->id,
            c_->id,
            r->getLifePoints(),
            r->p
        );
    }
    // Sst the red warrior of this city to null.
    r = nullptr;

    return s;
}

std::string City::moveForwardBlue( City* c_, const char* t_ ) {
    if ( b == nullptr ) return "";
    assert( c_->b == nullptr );

    // Move the blue warrior from i to i + 1;
    c_->b = b;
    // The actions that the blue warrior may perform when moving forward.
    b->move();
    // Output marching info.
    std::string s;
    // if city i + 1 is the blue headquarters,
    // notify that it has been occupied.
    if ( c_->c != nullptr ) {
        s = stringFormat(
            MATCH_OUTPUT_HEADQUARTER_FORMAT,
            t_,
            COLOR_NAMES[ blue ],
            b->getName(),
            b->id,
            COLOR_NAMES[ red ],
            b->getLifePoints(),
            b->p
        );
        s += c_->notifyOccupied( t_ );
    } else {
        s = stringFormat(
            MATCH_OUTPUT_FORMAT,
            t_,
            COLOR_NAMES[ blue ],
            b->getName(),
            b->id,
            c_->id,
            b->getLifePoints(),
            b->p
        );
    }
    // Sst the blue warrior of this city to null.
    b = nullptr;

    return s;
}

void City::wolfRobbing( const char* t ) {
    // Not enough warriors.
    if ( !r || !b ) return;

    // Both are wolf, do nothing.
    if ( r->t == wolf && b->t == wolf ) return;
    // red warrior is a wolf and blue's is not, red robs blue.
    else if ( r->t == wolf ) {
        assert( b->t != wolf );
        std::pair<Weapon_enum, size_t> p = r->rob( b, true );
        // Output robbing info.
        if ( p.second > 0 ) {
            std::cout << stringFormat(
                ROB_OUTPUT_FORMAT,
                t,
                COLOR_NAMES[ red ],
                r->getName(),
                r->id,
                p.second,
                WEAPON_NAMES[ p.first ],
                COLOR_NAMES[ blue ],
                b->getName(),
                b->id,
                id
            );
        }
    }
    // similarly, blue robs red.
    else if ( b->t == wolf ) {
        assert( r->t != wolf );
        std::pair<Weapon_enum, size_t> p = b->rob( r, true );
        // Output robbing info.
        if ( p.second > 0 ) {
            std::cout << stringFormat(
                ROB_OUTPUT_FORMAT,
                t,
                COLOR_NAMES[ blue ],
                b->getName(),
                b->id,
                p.second,
                WEAPON_NAMES[ p.first ],
                COLOR_NAMES[ red ],
                r->getName(),
                r->id,
                id
            );
        }
    }

    // both are not wolf, do nothing.
}

void City::startBattle( const char* t ) {
    // Not enough warriors to fight.
    if ( !r || !b ) return;
    l.debug( stringFormat( "Battle starts in city %ld\n", id ) );

    // Actions before a battle starts.
    r->organizeBeforeBattle();
    b->organizeBeforeBattle();

    // Toggling logic:
    // 0 ^ 1 -> 1
    // 1 ^ 1 -> 0
    // 0 ^ 0 -> 0
    // 1 ^ 0 -> 1
    bool attacking_order = isOdd ^ isToggleAttackingOrder;
    do {
        // Red warrior attacks first in an odd city.
        if ( attacking_order ) {
            l.debug( stringFormat(
                "red %s %ld attacks blue %s %ld\n", r->getName(), r->id, b->getName(), b->id
            ) );
            r->attack( b );
        }
        // Blue warrior attacks first in an even city.
        else {
            l.debug( stringFormat(
                "blue %s %ld attacks red %s %ld\n", b->getName(), b->id, r->getName(), r->id
            ) );
            b->attack( r );
        }

        // Switch to the another warrior attacking first.
        attacking_order = !attacking_order;

        if ( attacking_order == ( isOdd ^ isToggleAttackingOrder ) )
            l.debug( "Next Round -------------------------->\n" );
    } while( canAttack() );

    // Put all weapons from W_remained to W_lib after a battle.
    r->organizeAfterBattle();
    b->organizeAfterBattle();

    // Actions after battle.
    // Red warrior is dead.
    if ( r->isDead() && !b->isDead() ) {
        // Winner robs loser.
        b->rob( r );
        // Output the battling result.
        std::cout << stringFormat(
            BATTLE_ONE_DEAD_OUTPUT_FORMAT,
            t,
            COLOR_NAMES[ blue ],
            b->getName(),
            b->id,
            COLOR_NAMES[ red ],
            r->getName(),
            r->id,
            id,
            b->getLifePoints()
        );
        // Winner yells.
        b->yell( t, COLOR_NAMES[ blue ], b->id, id );
        // Free the red warrior.
        delete r;
        r = nullptr;
        return;
    }
    // Blue warrior is dead.
    else if ( b->isDead() && !r->isDead() ) {
        r->rob( b );
        std::cout << stringFormat(
            BATTLE_ONE_DEAD_OUTPUT_FORMAT,
            t,
            COLOR_NAMES[ red ],
            r->getName(),
            r->id,
            COLOR_NAMES[ blue ],
            b->getName(),
            b->id,
            id,
            r->getLifePoints()
        );
        r->yell( t, COLOR_NAMES[ red ], r->id, id );
        delete b;
        b = nullptr;
        return;
    }
    // Both are alive.
    else if( !r->isDead() && !b->isDead() ) {
        std::cout << stringFormat(
            BATTLE_BOTH_ALIVE_OUTPUT_FORMAT,
            t,
            COLOR_NAMES[ red ],
            r->getName(),
            r->id,
            COLOR_NAMES[ blue ],
            b->getName(),
            b->id,
            id
        );
        r->yell( t, COLOR_NAMES[ red ], r->id, id );
        b->yell( t, COLOR_NAMES[ blue ], b->id, id );
        return;
    }

    // Both are dead
    std::cout << stringFormat(
        BATTLE_BOTH_DEAD_OUTPUT_FORMAT,
        t,
        COLOR_NAMES[ red ],
        r->getName(),
        r->id,
        COLOR_NAMES[ blue ],
        b->getName(),
        b->id,
        id
    );
    delete r;
    r = nullptr;
    delete b;
    b = nullptr;
}

void City::addWarrior( Warrior* w ) {
    // No warrior generated from a commander.
    if ( w == nullptr ) return;

    // City where the red commander is.
    if ( c->c == red ) {
        assert( r == nullptr );
        r = w;
    }
        // City where the blue commander is.
    else {
        assert( c->c == blue );
        assert( b == nullptr );
        b = w;
    }
}

std::string City::notifyOccupied( const char* t ) {
    assert( c != nullptr );

    std::string s;
    // Store the warrior arriving the headquarters into a queue,
    // and report it as occupied.
    if ( c->c == red ) {
        // First time of being occupied, output the info.
        if ( !c->isOccupied() )
            s = stringFormat(
                OCCUPATION_OUTPUT_FORMAT,
                t,
                COLOR_NAMES[ red ]
            );
        // The blue warrior cannot null when the red headquarters is occupied.
        assert( b != nullptr );
        Q->push( b );
        b = nullptr;
    }
    else {
        assert( M_Assert(
            c->c == blue,
            stringFormat(
                "city(id=%ld), red_war(type=%s,id=%ld)",
                id,
                r->getName(),
                r->id
            ).c_str()
        ) );

        if ( !c->isOccupied() )
            s = stringFormat(
                OCCUPATION_OUTPUT_FORMAT,
                t,
                COLOR_NAMES[ blue ]
            );

        assert( r != nullptr );
        Q->push( r );
        r = nullptr;
    }

    // Must invoke after the output procedure.
    // Notify the commander that it has been occupied.
    c->setOccupied();
    return s;
}

void City::report( const char* t ) {
    if ( r ) r->report( t, COLOR_NAMES[ red ] );
    if ( b ) b->report( t, COLOR_NAMES[ blue ] );
}

void City::cleanUp() {
    // Free resources for the warriors in this city.
    if ( r ) { delete r; r = nullptr; }
    if ( b ) { delete b; b = nullptr; }

    // Free resources for the warriors arriving the headquarters.
    while ( Q != nullptr && !Q->empty() ) {
        delete Q->front();
        Q->pop();
    }
}

