/*
 * wow_war.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/10/2024
 */

#include "../include/wow_war.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// https://stackoverflow.com/questions/17764661/multiple-definition-of-linker-error
const char* COLOR_NAMES[] = {
    "red",
    "blue"
};

const char* WEAPON_NAMES[] = {
    "sword",
    "bomb",
    "arrow"
};

// https://brainly.com/question/49412407
// https://stackoverflow.com/questions/19929681/c-global-variable-declaration
const std::string WARRIOR_NAMES[ WARRIOR_NUM ] = {
    "dragon",
    "ninja",
    "iceman",
    "lion",
    "wolf"
};

// -------------------------------------------------------
// Weapon class
// -------------------------------------------------------

bool Weapon::Comparator::operator()( const Weapon *w1, const Weapon *w2 ) const {
    if ( w1->t == w2->t && w1->t == arrow ) {
        return w1->durability <= w2->durability;
    }

    return w1->t <= w2->t;
}

inline Weapon_enum Weapon::getType() const {
    return t;
}

inline bool Weapon::isBroken() const {
    return durability != 0;
}

inline void Weapon::consume() {
    assert( durability > 0 );

    durability--;
}

size_t Sword::get_damage( size_t p_ ) {
    return std::floor( p_ * 2 / 10.0 );
}

size_t Bomb::get_damage( size_t p_ ) {
    return std::floor( p_ * 4 / 10.0 );
}

size_t Arrow::get_damage( size_t p_ ) {
    return std::floor( p_ * 3 / 10.0 );
}

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

std::pair<Weapon_enum, size_t> Warrior::rob( Warrior *e, bool isBeforeBattle )  {
    // Put all weapons from W_remained to W_lib,
    // which is necessary after a battle.
    while ( !W_remained.empty() ) {
        W_lib.push( W_remained.front() );
        W_remained.pop();
    }

    size_t c = 0;
    Weapon* w_pre = nullptr;
    // Continue robbing iff weapon library isn't full and the enemy has weapons.
    while ( W_lib.size() < 10 && e->hasWeapons() ) {
        // Get a weapon with the smallest id.
        Weapon* w_c = e->peekWeapon();
        // Stop robbing when this robbing action happening before a battle and
        // getting a weapon with a larger id.
        if ( isBeforeBattle && w_pre != nullptr && w_pre->getType() != w_c->getType() ) break;
        // The enemy drops it.
        e->dropWeapon();
        // Tis warrior holds it.
        W_lib.push( w_c );
        w_pre = w_c;
        c++;
    }

    return std::pair<Weapon_enum, size_t>( w_pre == nullptr ? sword : w_pre->getType(), c );
}

void Warrior::attack( Warrior *e ) {
    assert( !isDead() );

    // First attack with weapons from the weapon library.
    if ( !W_lib.empty() ) {
        // Grab a weapon.
        Weapon* w = W_lib.top();
        // Free up memory for weapon arrow and bomb.
        if ( w_pre != nullptr && ( w_pre->getType() == arrow || w_pre->getType() == bomb ) ) delete w_pre;
        w_pre = w;
        // Attack the enemy.
        e->attacked( w, this, false );
        // Get damaged when using a bomb
        if ( w->getType() == bomb ) attacked( w, e, true );

        // Handling the weapon after attacking
        w->consume();
        // Push available weapons to W_remained for future use iff
        // it is used up or without durability
        if ( !w->isBroken() ) {
            // Only push weapons except for arrow and bomb to W_remained.
            if ( w->getType() != arrow || w->getType() != bomb ) W_remained.push( w );
            // Discard a broken weapon.
            W_lib.pop();
        }

        return;
    }

    // Attack with remained weapons
    // Note that there are no arrow or bomb in W_remained,
    // so no self-damage here.
    if ( !W_remained.empty() ) {
        // Grab a weapon.
        Weapon* w = W_remained.front();
        w_pre = w;
        W_remained.pop();
        // Attack the enemy.
        e->attacked( w, this, false );
        // Push it back to W_remained.
        W_remained.push( w );
    }
    // No weapons available, do nothing.
}

void Warrior::attacked( Weapon* w, Warrior* e, bool isSelf ) {
    // Damage caused by this attack.
    size_t d = 0;
    // Self-damage caused by using a bomb except for a ninja
    if ( w->getType() == bomb && isSelf && t != ninja ) {
        d = std::floor( std::abs( ( double ) e->p - p ) * 1 / 10.0 );
    }
    // Damage caused by other weapons.
    else { d = w->get_damage( e->p ); }

    // Calculate remained life points.
    if ( m <= d ) {
        m = 0;
        return;
    }

    m -= d;
}

// https://en.cppreference.com/w/cpp/utility/tuple
std::tuple<size_t, size_t, size_t> Warrior::countWeapons() {
    size_t c_s = 0; // sword number count
    size_t c_b = 0; // bomb number count
    size_t c_a = 0; // arrow number count

    // Assume all weapons are pushed into W_lib after a battle.
    while ( !W_remained.empty() ) {
        Weapon* w = W_remained.front();
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

        W_remained.pop();
        W_lib.push( w );
    }

    return { c_s, c_b, c_a };
}

inline void Warrior::report( const char* t, const char* c ) {
    std::tuple<size_t, size_t, size_t> n = countWeapons();

    printf(
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
const char* Dragon::OUT_FORMAT = "It has a %s,and it's morale is %.2f\n";
inline void Dragon::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->getType() ],
        morale
    );
}

void Dragon::yell( const char* t, const char* c, size_t id_w, size_t id_c ) {
    printf(
        "%s:40 %s dragon %ld yelled in city %ld\n",
        t, c, id_w, id_c
    );
}

// Ninjia ----------------------------------------------
const char* Ninjia::OUT_FORMAT = "It has a %s and a %s\n";
inline void Ninjia::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->getType() ],
        WEAPON_NAMES[ W_init[ 1 ]->getType() ]
    );
}

// Iceman ----------------------------------------------
const char* Iceman::OUT_FORMAT = "It has a %s\n";
inline void Iceman::print() {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->getType() ]
    );
}

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
inline void Lion::print() {
    printf(
        OUT_FORMAT,
        loyalty
    );
}

bool Lion::escape( const char* t, const char* c ) {
    if ( loyalty > 0 ) return false;

    printf(
        "%s:05 %s lion %ld ran away",
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

// -------------------------------------------------------
// class City
// -------------------------------------------------------

const char* City::MATCH_OUTPUT_FORMAT = "%s:10 %s %s %ld marched to city %ld with %ld elements and force %ld\n";
const char* City::ROB_OUTPUT_FORMAT = "%s:35 %s %s %ld took %ld %s from %s %s %ld in city %ld\n";
const char* City::BATTLE_ONE_DEAD_OUTPUT_FORMAT = "%s:40 %s %s %ld killed %s %s %ld in city %ld remaining %ld elements\n";
const char* City::BATTLE_BOTH_DEAD_OUTPUT_FORMAT = "%s:40 both %s %s %ld and %s %s %ld died in city %ld\n";
const char* City::BATTLE_BOTH_ALIVE_OUTPUT_FORMAT = "%s:40 both %s %s %ld and %s %s %ld were alive in city %ld\n";
const char* City::OCCUPATION_OUTPUT_FORMAT = "%s:10 %s headquarter was taken\n";

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

void City::moveForwardRed( City* c_, const char* t_ ) {
    if ( r == nullptr ) return;
    assert( c_->r == nullptr );

    // Move the red warrior from i to i + 1;
    c_->r = r;
    // The actions that the red warrior may perform when moving forward.
    r->move();
    // Output marching info.
    printf(
        MATCH_OUTPUT_FORMAT,
        t_,
        COLOR_NAMES[ red ],
        r->getName(),
        r->id,
        id,
        r->getLifePoints(),
        r->p
    );
    // if city i + 1 is the blue headquarters,
    // notify that it has been occupied.
    if ( c_->c != nullptr ) c_->notifyOccupied( t_ );
    // Sst the red warrior of this city to null.
    r = nullptr;
}

void City::moveForwardBlue( City* c_, const char* t_ ) {
    if ( b == nullptr ) return;
    assert( c_->b == nullptr );

    // Move the blue warrior from i to i + 1;
    c_->b = b;
    // The actions that the blue warrior may perform when moving forward.
    b->move();
    // Output marching info.
    printf(
        MATCH_OUTPUT_FORMAT,
        t_,
        COLOR_NAMES[ blue ],
        b->getName(),
        b->id,
        id,
        b->getLifePoints(),
        b->p
    );
    // if city i + 1 is the blue headquarters,
    // notify that it has been occupied.
    if ( c_->c != nullptr ) c_->notifyOccupied( t_ );
    // Sst the blue warrior of this city to null.
    b = nullptr;
}

void City::wolfRobbing( const char* t ) {
    // Both are wolf, do nothing.
    if ( r->t == wolf && b->t == wolf ) return;
    // red warrior is a wolf and blue's is not, red robs blue.
    else if ( r->t == wolf ) {
        assert( b->t != wolf );
        std::pair<Weapon_enum, size_t> p = r->rob( b, true );
        // Output robbing info.
        if ( p.second > 0 ) {
            printf(
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
            printf(
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

    bool attacking_order = isOdd;
    do {
        // Red warrior attacks first in an odd city.
        if ( attacking_order ) {
            r->attack( b );
            b->attack( r );
        }
        // Blue warrior attacks first in an even city.
        else {
            b->attack( r );
            r->attack( b );
        }

        // Switch to the another warrior.
        attacking_order = !attacking_order;
    } while( r->canAttack() || b->canAttack() );

    // Actions after battle.
    // Red warrior is dead.
    if ( r->isDead() && !b->isDead() ) {
        // Winner robs loser.
        b->rob( r );
        // Output the battling result.
        printf(
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
        return;
    }
    // Blue warrior is dead.
    else if ( b->isDead() && !r->isDead() ) {
        r->rob( b );
        printf(
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
        return;
    }
    // Both are alive.
    else if( !r->isDead() && !b->isDead() ) {
        printf(
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
    printf(
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
    delete b;
}

void City::addWarrior( Warrior* w ) {
    // No warrior generated from a commander.
    if ( w == nullptr ) return;

    // City where the red commander is.
    if ( r != nullptr ) r = w;
    // City where the blue commander is.
    else if ( b != nullptr ) b = w;
    // Cities in between.
}

void City::notifyOccupied( const char* t ) {
    assert( c != nullptr );

    // Notify the commander that it has been occupied.
    c->setOccupied();
    // Store the warrior arriving the headquarters into a queue,
    // and report it as occupied.
    if ( r ) {
        assert( c->c == red );

        printf(
            OCCUPATION_OUTPUT_FORMAT,
            t,
            COLOR_NAMES[ red ]
        );
        Q->push( r );
        r = nullptr;
    }
    else {
        assert( b );
        assert( c->c == blue );

        printf(
            OCCUPATION_OUTPUT_FORMAT,
            t,
            COLOR_NAMES[ blue ]
        );
        Q->push( b );
        b = nullptr;
    }
}

inline void City::report( const char* t ) {
    if ( r ) r->report( t, COLOR_NAMES[ red ] );
    if ( b ) b->report( t, COLOR_NAMES[ blue ] );
}

// -------------------------------------------------------
// class WorldOfWarcraft
// -------------------------------------------------------

const int WorldOfWarcraft::WARRIOR_NAMES_RED[ WARRIOR_NUM ] = {
    iceman,
    lion,
    wolf,
    ninja,
    dragon
};

const int WorldOfWarcraft::WARRIOR_NAMES_BLUE[ WARRIOR_NUM ] = {
    lion,
    dragon,
    ninja,
    iceman,
    wolf
};

// https://www.geeksforgeeks.org/how-to-add-leading-zeros-to-a-cpp-string/
std::string WorldOfWarcraft::getTimeStr( size_t c ) {
    std::string s = std::to_string( c );
    assert( s.size() < 4 );

    switch ( s.size() ) {
        // e.g. 1 => 001
        case 1:
            s.insert( 0, 2, '0' );
            break;
            // e.g. 22 => 022
        case 2:
            s.insert( 0, 1, '0' );
            break;
    }

    return s;
}

inline bool WorldOfWarcraft::hasTime( int t ) const {
    // This conditional statement also includes the situation
    // where the t == 0, i.e. the game finishes as soon as each commander generates a warrior.
    return t - c * 60 >= 0;
}

void WorldOfWarcraft::lionEscaping( int t_, const char* t_str ) {
    if ( t_ < 0 ) return;

    // Lion-escaping may happen in city 0 and city N + 1
    // when a lion with loyalty <= 0 in the beginning.
    for ( size_t i = 0; i < n + 2; i++ ) {
        C[ i ]->lionEscaping( t_str );
    }
}

void WorldOfWarcraft::moveForward( int t, const char* t_str  ) {
    if ( t < 0 ) return;

    // Don't forget city 0 and N + 1.
    for ( int i = n + 1; i > 0; i-- ) {
        // Start from west to east.
        // i.e. move a red warrior at city i to i + 1
        C[ i - 1 ]->moveForwardRed( C[ i ], t_str );
    }

    for ( size_t i = 0; i < n + 1; i++ ) {
        // Start from east to west.
        // i.e. move a blue warrior at city i to i - 1.
        C[ i + 1 ]->moveForwardBlue( C[ i ], t_str );
    }
}

void WorldOfWarcraft::wolfRobbing( int t, const char* t_str ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->wolfRobbing( t_str );
    }
}

void WorldOfWarcraft::startBattle( int t, const char* t_str ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->startBattle( t_str );
    }
}

void WorldOfWarcraft::report( int t, const char* t_str ) {
    // XXX:50 - headquarters report remained life points
    if ( t - 50 >= 0 ) {
        comm_red.report( t_str );
        comm_blue.report( t_str );
    }

    // XXX:55 - Warriors report their owned weapons.
    if ( t - 55 >= 0 ) {
        // Warriors arriving the headquarters don't report.
        for ( size_t i = 0; i < n; i++ ) {
            C[ i ]->report( t_str );
        }
    }
}

void WorldOfWarcraft::start(
    size_t m_, size_t n_, size_t k_, int t_,
    const size_t* M_, const size_t* P_
) {
    // Resource initialization
    c = 0; // Time starting at 000:00
    n = n_; // Number of cities excluding 0 and N + 1
    // Initialize the city list
    C = new City* [ n + 2 ];
    for ( size_t i = 0; i < n + 2; i++ ) {
        if ( i == 0 ) C[ i ] = new City( i % 2 != 0, &comm_red ); // city 0
        else if ( i == n + 1 ) C[ i ] = new City( i % 2 != 0, &comm_blue ); // city N + 1
        else C[ i ] = new City( i % 2 != 0, nullptr ); // cities in between
    }
    // Commander initialization.
    comm_red.initResource( m_, k_, M_, P_ );
    comm_blue.initResource( m_, k_, M_, P_ );

    // Start the game.
    const char* s = nullptr;
    while ( hasTime( t_ ) ) {
        s = getTimeStr( c ).c_str();

        // XXX:00 - generate a warrior by consuming life points.
        // Each headquarter generates a warrior if possible.
        // and report the warriors it generates.
        Warrior* w_red = comm_red.generate( s );
        if ( w_red ) w_red->print();
        Warrior* w_blue = comm_blue.generate( s );
        if ( w_blue ) w_blue->print();

        // Add warriors to the two cities.
        C[ 0 ]->addWarrior( w_red );
        C[ n + 1 ]->addWarrior( w_blue );

        // Time remained with respect to hours.
        int t_remained = t_ - c * 60;
        // XXX:05 - Lion whose loyalty <= 0 escapes.
        lionEscaping( t_remained - 5, s );
        // XXX:10 - move one step forward
        moveForward( t_remained - 10, s );
        // XXX:35 - Wolf robbing action;
        wolfRobbing( t_remained - 35, s );
        // XXX:40 - battle starts
        startBattle( t_remained - 40, s );
        // Reporting events.
        report( t_remained, s );

        // Increment the timestamp by one hour.
        c++;
    }

    // Don't need code to handle additional time,
    // since we start time counting from 0. e.g.
    // if t = 60, 60 - 0 * 60 = 60 >= 0.
    // would go through all events in that 60 mins,
    // Similarly, t = 80, 80 - 0 * 60 = 80 >= 0,
    // handle events in the first hour/60 mins,
    // and 80 - 1 * 60 = 20 >= 0,
    // handle events in the remained 20 mins.
}

// -------------------------------------------------------
// class Commander
// -------------------------------------------------------

// https://www.geeksforgeeks.org/cpp-printf-function/
const char* Commander::OUTPUT_FORMAT = "%s %s %s %d born with strength %d,%d %s in %s headquarter\n";

Warrior* Commander::getWarrior(
    Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_
) const {
    switch ( t_ ) {
        case dragon:
            return new Dragon( warrior_m_, p_, n_, m_ );
        case ninja:
            return new Ninjia( warrior_m_, p_, n_ );
        case iceman:
            return new Iceman( warrior_m_, p_, n_ );
        case lion:
            return new Lion( warrior_m_, p_, n_, m_, k );
        case wolf:
            return new Wolf( warrior_m_, p_, n_ );
        default:
            assert( false );
            return nullptr;
    }
}

int Commander::hasNext() {
    // Have to explicitly cast M[ W_n[ ( idx + 1 ) % WARRIOR_NUM ] ] to int,
    // otherwise the result will always be unsigned int, which is never less than 0.
    if ( m - ( int ) M[ W_n[ ( idx + 1 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 1 ) % WARRIOR_NUM;
    else if ( m - ( int ) M[ W_n[ ( idx + 2 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 2 ) % WARRIOR_NUM;
    else if ( m - ( int ) M[ W_n[ ( idx + 3 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 3 ) % WARRIOR_NUM;
    else if ( m - ( int ) M[ W_n[ ( idx + 4 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 4 ) % WARRIOR_NUM;
    else if ( m - ( int ) M[ W_n[ ( idx + 5 ) % WARRIOR_NUM ] ] >= 0 )
        return ( idx + 5 ) % WARRIOR_NUM;

    return -1;
}

void Commander::initResource( int m_, size_t k_, const size_t* M_, const size_t* P_ ) {
    m = m_;
    k = k_;
    M = M_;
    P = P_;
    n = 0;
    std::fill( std::begin( C ), std::end( C ), 0 );
    idx = -1;
    is_stopped = false;
    is_occupied = false;
}

Warrior* Commander::generate( const char* t ) {
    // Has been occupied, no actions.
    if ( is_occupied ) return nullptr;

    // Otherwise, try to generate a warrior.
    idx = hasNext();
    // Has the ability to generate a warrior?
    if ( idx < 0 ) {
        // No, output terminating text if necessary.
        if ( !is_stopped ) {
            is_stopped = !is_stopped;
            printf(
                "%s %s headquarter stops making warriors\n",
                t,
                COLOR_NAMES[ c ]
            );
        }

        return nullptr;
    }

    // Yes, get the info of the warrior.
    int idx_global = W_n[ idx ]; // Global warrior enum idx.
    size_t warrior_m = M[ idx_global ];
    const char *color_name = COLOR_NAMES[ c ];
    const char *warrior_name = WARRIOR_NAMES[ idx_global ].c_str();

    // Reduce total life points.
    m -= warrior_m;
    // Output the production text.
    // https://stackoverflow.com/questions/10865957/how-to-use-printf-with-stdstring
    printf(
        OUTPUT_FORMAT,
        t, // timestamp
        color_name,
        warrior_name,
        ++n, // Number
        warrior_m, // life/strength point
        ++C[ idx ], // Warrior count
        warrior_name,
        color_name
    );
    // Generate the warrior instance and return to the game coordinator.
    return getWarrior(
        static_cast<Warrior_enum>( idx_global ),
        warrior_m, 0, n, m
    );
}

inline void Commander::report( const char* t ) {
    printf(
        "%s:50 %d elements in %s headquarter\n",
        t,
        m,
        COLOR_NAMES[ c ]
    );
}

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller() {
    size_t c; // Number of test cases.
    size_t m; // Total life points.
    size_t n; // Number of cities.
    size_t k; // Loyalty consumption points
    size_t t; // Time
    size_t M[ WARRIOR_NUM ]; // Life points.
    size_t P[ WARRIOR_NUM ]; // Power points.
    WorldOfWarcraft wow = WorldOfWarcraft(); // Game coordinator

    std::cin >> c;
    for ( int i = 1; i <= c; i++ ) {
        std::cout << "Case:" << i << std::endl;

        std::cin >> m;
        assert( 1 <= m && m <= 100000 );
        std::cin >> n;
        assert( 1 <= n && n <= 20 );
        std::cin >> k;
        assert( 0 <= k && k <= 100 );
        std::cin >> t;
        assert( 0 <= t && t <= 6000 );

        for ( size_t &j : M ) {
            std::cin >> j;
            assert( 0 < j && j <= 200 );
        }

        for ( size_t &j : P ) {
            std::cin >> j;
            assert( 0 < j && j <= 200 );
        }

        wow.start( m, n, k, t, M, P );
    }
}

