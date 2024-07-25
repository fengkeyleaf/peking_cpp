/*
 * wow_weapon_submit_ver2.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 7/11/2024
 */

#include <iostream>
#include <string>
#include <queue>
#include <cassert>
#include <cmath>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#define WARRIOR_NUM 5
#define WEAPON_NUM 3

// https://stackoverflow.com/questions/17764661/multiple-definition-of-linker-error
const char *COLOR_NAMES[] = {
    "red",
    "blue"
};

const char *WEAPON_NAMES[] = {
    "sword",
    "bomb",
    "arrow"
};

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

// -------------------------------------------------------
// Weapon class
// -------------------------------------------------------

class Weapon {
protected:
    const Weapon_enum t; // id
    const size_t damage;
    int durability; // -1 no durability, 0 broken, >= 1 normal.

public:
    Weapon( Weapon_enum t_, size_t da_, size_t dur_ ) : t( t_ ), damage( da_ ), durability( dur_ ) {}

    Weapon_enum get_type() const;
};

class Sword : public Weapon {
public:
    Sword( size_t p_ ) : Weapon( sword, std::floor( p_ * 2 / 10.0 ), -1 ) {}
};

class Bomb : public Weapon  {
public:
    Bomb( size_t p_ ) : Weapon( bomb, std::floor( p_ * 4 / 10.0 ), 1 ) {}
};

class Arrow : public Weapon {
public:
    Arrow( size_t p_ ) : Weapon( arrow, std::floor( p_ * 3 / 10.0 ), 2 ) {}
};

Weapon_enum Weapon::get_type() const {
    return t;
}

// -------------------------------------------------------
// Warrior class
// -------------------------------------------------------

// https://en.cppreference.com/w/cpp/language/abstract_class
class Warrior {
protected:
    const size_t id; // ID
    const Warrior_enum t; // Type
    const size_t p; // power
    size_t m; // Life points.
    // https://www.geeksforgeeks.org/pointer-array-array-pointer/
    Weapon* (*W_init) = nullptr; // Initialized weapons.
    std::priority_queue<Weapon*> W_lib; // Weapon library.

    Warrior( size_t id_, Warrior_enum t_, size_t p_, size_t m_ ) : id( id_ ), t( t_ ), p( p_ ), m( m_ ) {}

    Weapon* get_weapon( Weapon_enum t_, size_t p_ );

public:
    virtual ~Warrior() {
        delete [] W_init;

        while ( !W_lib.empty() ) {
            delete W_lib.top();
            W_lib.pop();
        }
    }

    virtual void print() = 0;
};

class Dragon: public Warrior {
    const static char* OUT_FORMAT;
    double morale;

public:
    Dragon( size_t id_, size_t m_, size_t p_, size_t n_, size_t m_remained )
        : Warrior( id_, dragon, p_, m_ ), morale( ( double ) m_remained / m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % 3 ), p_ );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;
};

class Ninjia: public Warrior {
    const static char* OUT_FORMAT;

public:
    Ninjia( size_t id_, size_t m_, size_t p_, size_t n_ )
        : Warrior( id_, ninja, p_, m_ ) {
        W_init = new Weapon*[ 2 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ), p_ );
        W_init[ 1 ] = get_weapon( static_cast<Weapon_enum>( ( n_ + 1 ) % WEAPON_NUM ), p_ );
        W_lib.push( W_init[ 0 ] );
        W_lib.push( W_init[ 1 ] );
    }

    void print() override;
};

class Iceman: public Warrior {
    const static char* OUT_FORMAT;

public:
    Iceman( size_t id_, size_t m_, size_t p_, size_t n_ )
        : Warrior( id_, iceman, p_, m_ ) {
        W_init = new Weapon*[ 1 ];
        W_init[ 0 ] = get_weapon( static_cast<Weapon_enum>( n_ % WEAPON_NUM ), p_ );
        W_lib.push( W_init[ 0 ] );
    }

    void print() override;
};

class Lion: public Warrior {
    const static char* OUT_FORMAT;
    size_t loyalty;

public:
    Lion( size_t id_, size_t m_, size_t p_, size_t m_remained )
        : Warrior( id_, lion, p_, m_ ), loyalty( m_remained ) {}

    void print() override;
};

class Wolf: public Warrior {

public:
    Wolf( size_t id_, size_t m_, size_t p_ ) : Warrior( id_, wolf, p_, m_ ) {}

    void print() override {}
};

// -------------------------------------------------------
// Warrior class
// -------------------------------------------------------

Weapon *Warrior::get_weapon( Weapon_enum t_, size_t p_ ) {
    switch ( t_ ) {
        case sword:
            return new Sword( p_ );
        case bomb:
            return new Bomb( p_ );
        case arrow:
            return new Arrow( p_ );
        default:
            assert( false );
            return nullptr;
    }
}

const char* Dragon::OUT_FORMAT = "It has a %s,and it's morale is %.2f\n";
void Dragon::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ],
        morale
    );
}

const char* Ninjia::OUT_FORMAT = "It has a %s and a %s\n";
void Ninjia::print()  {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ],
        WEAPON_NAMES[ W_init[ 1 ]->get_type() ]
    );
}

const char* Iceman::OUT_FORMAT = "It has a %s\n";
void Iceman::print() {
    printf(
        OUT_FORMAT,
        WEAPON_NAMES[ W_init[ 0 ]->get_type() ]
    );
}

const char* Lion::OUT_FORMAT = "It's loyalty is %ld\n";
void Lion::print() {
    printf(
        OUT_FORMAT,
        loyalty
    );
}

// -------------------------------------------------------
// Game class
// -------------------------------------------------------

class Commander {
    const static std::string WARRIOR_NAMES[ WARRIOR_NUM ]; // global warrior names
    const static char* OUTPUT_FORMAT;

    const Color_enum c; // color
    int m; // total life points
    const int *W_n; // local warrior names
    const size_t *M; // Warrior life points
    size_t n = 0; // warrior total count
    size_t C[ WARRIOR_NUM ] = { 0 }; // warrior count
    int idx = -1; // warrior index
    bool is_stopped = false;

    /**
     * Generate a warrior, but only print out its info for this assignment.
     *
     * @param t_ Warrior enum type.
     * @param warrior_m_ Warrior life point.
     * @param n_ Number id.
     * @param m_ Remained life points.
     * */

    Warrior* get_warrior( size_t id_, Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_ );

public:
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

    void generate( std::string &t );

    /**
     * Initialize resources.
     *
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void initResource( int m, const size_t *M );
};

// -------------------------------------------------------
// class Commander
// -------------------------------------------------------

// https://brainly.com/question/49412407
const std::string Commander::WARRIOR_NAMES[ WARRIOR_NUM ] = {
    "dragon",
    "ninja",
    "iceman",
    "lion",
    "wolf"
};

// https://www.geeksforgeeks.org/cpp-printf-function/
const char* Commander::OUTPUT_FORMAT = "%s %s %s %d born with strength %d,%d %s in %s headquarter\n";

Warrior* Commander::get_warrior(
    size_t id_, Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_
) {
    switch ( t_ ) {
        case dragon:
            return new Dragon( id_, warrior_m_, p_,  n_, m_ );
        case ninja:
            return new Ninjia( id_, warrior_m_, p_, n_ );
        case iceman:
            return new Iceman( id_, warrior_m_, p_, n_ );
        case lion:
            return new Lion( id_, warrior_m_, p_, m_ );
        case wolf:
            return new Wolf( id_, warrior_m_, p_ );
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

void Commander::initResource( int m, const size_t *M ) {
    this->m = m;
    this->M = M;
    n = 0;
    std::fill( std::begin( C ), std::end( C ), 0 );
    idx = -1;
    is_stopped = false;
}

void Commander::generate( std::string &t ) {
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

        return;
    }

    // Yes, get the info of the warrior.
    int idx_global = W_n[ idx ];
    size_t warrior_m = M[ idx_global ];
    const char *color_name = COLOR_NAMES[ c ];
    const char *warrior_name = WARRIOR_NAMES[ idx_global ].c_str();

    // Reduce total life points.
    m -= warrior_m;
    // Output the production text.
    // https://stackoverflow.com/questions/10865957/how-to-use-printf-with-stdstring
    printf(
        OUTPUT_FORMAT,
        t.c_str(), // timestamp
        color_name,
        warrior_name,
        ++n, // Number
        warrior_m, // life/strength point
        ++C[ idx ], // Warrior count
        warrior_name,
        color_name
    );
    // Output the text for the warrior
    Warrior* w = get_warrior(
        n, static_cast<Warrior_enum>( idx_global ), warrior_m, 0, n, m
    );
    w->print();
    delete w;
}

class WorldOfWarcraft {
    const static int WARRIOR_NAMES_RED[ WARRIOR_NUM ];
    const static int WARRIOR_NAMES_BLUE[ WARRIOR_NUM ];

    unsigned int c = 0; // timestamp count
    Commander comm_red = Commander( red, WARRIOR_NAMES_RED ); // red headquarter
    Commander comm_blue = Commander( blue, WARRIOR_NAMES_BLUE ); // blue headquarter

    static std::string getTimeStr( size_t c );

public:
    /**
     * Start the game.
     *
     * @param n Case number.
     * @param m Total life points.
     * @param M Array to indicate life points to generate a warrior.
     * */

    void start( size_t n, size_t m, const size_t *M );
};


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

void WorldOfWarcraft::start( size_t n, size_t m, const size_t *M  ) {
    std::cout << "Case:" << n << std::endl;

    c = 0;
    comm_red.initResource( m, M );
    comm_blue.initResource( m, M );

    std::string s;
    while ( comm_red.hasNext() >= 0 || comm_blue.hasNext() >= 0 ) {
        s = getTimeStr( c );
        comm_red.generate( s );
        comm_blue.generate( s );
        c++;
    }

    s = getTimeStr( c );
    comm_red.generate( s );
    comm_blue.generate( s );
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
// Entry function
// -------------------------------------------------------

void caller() {
    int n, m;
    size_t M[ WARRIOR_NUM ];
    WorldOfWarcraft wow = WorldOfWarcraft();

    std::cin >> n;
    for ( int i = 1; i <= n; i++ ) {
        std::cin >> m;

        for ( size_t &j : M ) {
            std::cin >> j;
        }

        wow.start( i, m, M );
    }
}

int main() {

    caller();

    return 0;
}