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

Weapon_enum Weapon::get_type() const {
    return t;
}

bool Weapon::hasDurability() const {
    return durability != 0;
}

void Weapon::consume() {
    if ( durability <= 0 ) return;

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

Weapon* Warrior::get_weapon( Weapon_enum t_ ) {
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

void Warrior::attack( Warrior *e ) {
    if ( isDead() ) return;

    if ( !W_lib.empty() ) {
        Weapon* w = W_lib.top();
        w_pre = w;
        e->attacked( w, this, false );
        if ( w->get_type() == bomb ) attacked( w, this, true );

        w->consume();
        if ( !( w->get_type() == arrow && w->hasDurability() ) ) {
            if ( w->get_type() != arrow || w->get_type() != bomb ) W_remained.push( w );
            W_lib.pop();
        }

        return;
    }

    if ( !W_remained.empty() ) {
        Weapon* w = W_remained.front();
        w_pre = w;
        W_remained.pop();
        e->attacked( w, this, false );
        W_remained.push( w );
    }
}

void Warrior::attacked( Weapon* w, Warrior* e, bool isSelf ) {
    size_t d = 0;
    if ( w->get_type() == bomb && isSelf ) {
        d = std::floor( std::abs( ( double ) e->p - p ) * 1 / 10.0 );
    }
    else { d = w->get_damage( e->p ); }

    if ( m <= d ) {
        m = 0;
        return;
    }

    m -= d;
}

void Warrior::dropWeapon() {
    assert( !W_lib.empty() );

    W_lib.pop();
}

// Dragon ----------------------------------------------
const char* Dragon::OUT_FORMAT = "It has a %s,and it's morale is %.2f\n";
inline void Dragon::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ],
        morale
    );
}

void Dragon::yell( const char* t, const char* c, size_t id_w, size_t id_c ) {
    printf(
        "%s:40 %s dragon %ld yelled in city %ld",
        t, c, id_w, id_c
    );
}

// Ninjia ----------------------------------------------
const char* Ninjia::OUT_FORMAT = "It has a %s and a %s\n";
inline void Ninjia::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ],
        WEAPON_NAMES[ W_init[ 1 ]->get_type() ]
    );
}

void Ninjia::attacked( Weapon *w, Warrior* e, bool isSelf ) {
    if ( w->get_type() == bomb && isSelf ) {

    }
}

// Iceman ----------------------------------------------
const char* Iceman::OUT_FORMAT = "It has a %s\n";
inline void Iceman::print() {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ]
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

const char* City::MATCH_OUTPUT_FORMAT = "%s:10 %s %s %ld marched to city %ld with %ld elements and force %ld";
const char* City::ROB_OUTPUT_FORMAT = "%:35 %s %s %ld took %ld %s from %s %s %ld in city %ld";

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
    if ( c_->c != nullptr ) c_->notifyOccupied();
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
    if ( c_->c != nullptr ) c_->notifyOccupied();
    // Sst the blue warrior of this city to null.
    b = nullptr;
}

void City::wolfRobbing() {
    // Both are wolf, do nothing.
    if ( r->t == wolf && b->t == wolf ) return;
    // red warrior is a wolf and blue's is not, red robs blue.
    else if ( r->t == wolf ) {
        assert( b->t != wolf );
        std::pair<Weapon_enum, size_t> p = r->rob( b );
        // Output robbing info.
        if ( p.second > 0 ) {
            printf(
                ROB_OUTPUT_FORMAT,
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
        std::pair<Weapon_enum, size_t> p = b->rob( r );
        // Output robbing info.
        if ( p.second > 0 ) {
            printf(
                ROB_OUTPUT_FORMAT,
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

void City::startBattle() {
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
    // Blue warrior is dead.
    if ( r->isDead() && !b->isDead() ) {
        b->rob( r );
        b->yell();
        delete r;
        return;
    }
    // Red warrior is dead.
    else if ( b->isDead() && !r->isDead() ) {
        r->rob( b );
        r->yell();
        delete b;
        return;
    }
    // Both are alive.
    else if( !r->isDead() && !b->isDead() ) {
        r->yell();
        b->yell();
        return;
    }
    // Both are dead
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

void City::notifyOccupied() {
    assert( c != nullptr );

    // Notify the commander that it has been occupied.
    c->set_occupied();
    // Store the warrior arriving the headquarters into a queue.
    if ( r ) {
        Q.push( r );
        r = nullptr;
    }
    else {
        assert( b );
        Q.push( b );
        b = nullptr;
    }
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

inline bool WorldOfWarcraft::hasTime( int t ) const {
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

void WorldOfWarcraft::moveForward( int t, Warrior* r, Warrior* b, const char* t_str  ) {
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

void WorldOfWarcraft::wolfRobbing( int t ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->wolfRobbing();
    }
}

void WorldOfWarcraft::startBattle( int t ) {
    if ( t < 0 ) return;

    for ( size_t i = 0; i < n; i++ ) {
        C[ i ]->startBattle();
    }
}

void WorldOfWarcraft::report( int t ) {
    // XXX:50 - headquarters report remained life points
    if ( t - 50 >= 0 ) {
        comm_red.report();
        comm_blue.report();
    }

    // XXX:55 - Warriors report their owned weapons.
    if ( t - 55 >= 0 ) {
        // TODO: report warrior.
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

        // Each headquarter generates a warrior if possible.
        // and report the warriors generated.
        Warrior* w_red = comm_red.generate( s );
        if ( w_red ) w_red->print();
        Warrior* w_blue = comm_blue.generate( s );
        if ( w_blue ) w_blue->print();

        // Add warriors to the two cities.
        C[ 0 ]->addWarrior( w_red );
        C[ n + 1 ]->addWarrior( w_blue );

        // Time remained with respect to one hour.
        int t_remained = t_ - c * 60;
        // XXX:05 - Lion whose loyalty <= 0 escapes.
        lionEscaping( t_remained - 5, s );
        // XXX:10 - move one step forward
        moveForward( t_remained - 10, w_red, w_blue, s );
        // XXX:35 - Wolf robbing action;
        wolfRobbing( t_remained - 35 );
        // XXX:40 - battle starts
        startBattle( t_remained - 40 );
        // Reporting events.
        report( t_remained );

        // Increment the timestamp by one hour.
        c++;
    }

    // TODO: need code?
}

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

// -------------------------------------------------------
// class Commander
// -------------------------------------------------------

// https://www.geeksforgeeks.org/cpp-printf-function/
const char* Commander::OUTPUT_FORMAT = "%s %s %s %d born with strength %d,%d %s in %s headquarter\n";

Warrior* Commander::get_warrior(
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
                t.c_str(),
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
    return get_warrior(
        static_cast<Warrior_enum>( idx_global ),
        warrior_m, 0, n, m
    );
}

void Commander::report() {

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

