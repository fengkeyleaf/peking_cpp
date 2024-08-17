/*
 * wow_war_submit.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/16/2024
 */

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>
#include <queue>
#include <cassert>

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

// Reference:
// https://www.geeksforgeeks.org/logging-system-in-cpp/

// Enum to represent log levels
enum LogLevel {
    DEBUG, // 0
    INFO, // 1
    WARNING, // 2
    ERROR,  // 3
    CRITICAL // 4
};

class Logger {
    LogLevel l = WARNING;

    // Converts log level to a string for output
    static std::string levelToString( LogLevel level ) {
        switch ( level ) {
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }

    void log( LogLevel ll, const char* m );

public:
    // Constructor: Opens the log file in append mode
    Logger() {}

    Logger( LogLevel l_ ) : l( l_ ) {}

    // Destructor: Closes the log file
    ~Logger() {}

    // Logs a message with a given log level
    // https://stackoverflow.com/questions/5057021/why-do-inline-functions-have-to-be-defined-in-a-header-file
    void debug( const char* m ) {
        log( DEBUG, m );
    }

    void debug( const std::string& m ) {
        debug( m.c_str() );
    }

    void info( const char* m ) {
        log( INFO, m );
    }

    void info( const std::string& m ) {
        info( m.c_str() );
    }
};

void Logger::log( LogLevel ll, const char* m ) {
    if ( ll < l ) return;

    // Get current timestamp
    time_t now = time( 0 );
    tm *timeinfo = localtime( &now );
    char timestamp[20];
    std::strftime( timestamp, sizeof( timestamp ),
                   "%Y-%m-%d %H:%M:%S", timeinfo );

    // Create log entry
    std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] "
             << levelToString( ll ) << ": " << m;

    // Output to console
    std::cout << logEntry.str();
}

// https://stackoverflow.com/questions/3692954/add-custom-messages-in-assert
// M_Assert(ptr != nullptr, "MyFunction: requires non-null argument");
#ifndef NDEBUG
#   define M_Assert( Expr, Msg ) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_Assert(Expr, Msg) ;
#endif

bool __M_Assert( const char *expr_str, bool expr, const char *file, int line, const char *msg );

bool __M_Assert(
    const char *expr_str, bool expr, const char *file, int line, const char *msg
) {
    if ( !expr ) {
        std::cerr << "Assert failed message:\t" << msg << std::endl;
    }

    return expr;
}

// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template<typename ... Args>
std::string stringFormat( const char* format, Args ... args ) {
    int size_s = std::snprintf( nullptr, 0, format, args ... ) + 1; // Extra space for '\0'
    if ( size_s <= 0 ) { throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[size] );
    std::snprintf( buf.get(), size, format, args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

#define WARRIOR_NUM 5
#define WEAPON_NUM 3
#define MAX_CITY_NUM 20 // Excluding city 0 and city N + 1

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
    bool isUsedWeapon = false; // Did use weapon this round?
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
               // Used a weapon this round. either it is for the first time or
               ( isUsedWeapon && ( w_pre == nullptr ||
                                   // previously used weapon is bomb or arrow
                                   w_pre->getType() == bomb || w_pre->getType() == arrow ) );
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

    /**
     * Discard all weapons
     * */

    void discardAllWeapons();

    /**
     * Add a weapon to this warrior.
     * */

    void addWeapon( Weapon* w );

    /**
     * Heal this warrior.
     *
     * @param hp healing points.
     * */

    void heal( size_t hp );

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
    Wolf( size_t m_, size_t p_, size_t n_, Logger& l_ )
        : Warrior( n_, wolf, p_, m_, l_ ) {}

    std::string print() override;
};

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
    Weapon* w_pre_ = nullptr;
    // Continue robbing iff the weapon library isn't full and the enemy has weapons.
    while ( W_lib.size() < 10 && e->hasWeapons() ) {
        // Get a weapon with the smallest id.
        Weapon* w_c = e->peekWeapon();
        // Rob before battle -> wolf robbing for the current implementation.
        // i.e. only rob weapons with the smallest id.
        if ( isBeforeBattle && w_pre_ != nullptr && w_pre_->getType() != w_c->getType() ) break;
        // The enemy drops it.
        e->dropWeapon();
        // Tis warrior holds it.
        W_lib.push( w_c );
        w_pre_ = w_c;
        c++;
    }

    return std::pair<Weapon_enum, size_t>( w_pre_ == nullptr ? sword : w_pre_->getType(), c );
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

        // Used a weapon this round.
        isUsedWeapon = true;
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

        // Used a weapon this round.
        isUsedWeapon = true;
        // logging
        attackLogging( w, e );
    }
    // No weapons available, do nothing.
    // Don't forget to set variables properly.
    isUsedWeapon = false; // Not used a weapon this round.
    e->m_pre = e->m; // We know for sure that no damage to the enemy at this point.

    // Delete the last broken weapon if necessary.
    freeWeapon();
}

void Warrior::organizeBeforeBattle() {
    m_pre = m;
}

void Warrior::organizeAfterBattle() {
    // Put all weapons back to W_lib first.
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
    // Free up the weapon to which w_pre is pointing if there is a one.
    freeWeapon();
}

void Warrior::discardAllWeapons() {
    assert( W_remained.empty() );

    while( !W_lib.empty() ) {
        delete W_lib.top();
        W_lib.pop();
    }
}

void Warrior::addWeapon( Weapon *w ) {
    assert( W_remained.empty() );

    W_lib.push( w );
}

void Warrior::heal( size_t hp ) {
    // Overflow check.
    assert( m + hp >= m );

    m += hp;
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

// https://www.geeksforgeeks.org/cpp-printf-function/
const char* Commander::OUTPUT_FORMAT = "%s:00 %s %s %d born\n";

Warrior* Commander::getWarrior(
    Warrior_enum t_, size_t warrior_m_, size_t p_, size_t n_, int m_
) const {
    switch ( t_ ) {
        case dragon:
            return new Dragon( warrior_m_, p_, n_, m_, l );
        case ninja:
            return new Ninjia( warrior_m_, p_, n_, l );
        case iceman:
            return new Iceman( warrior_m_, p_, n_, l );
        case lion:
            return new Lion( warrior_m_, p_, n_, m_, k, l );
        case wolf:
            return new Wolf( warrior_m_, p_, n_, l );
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
    int idx_ = hasNext();
    // Doesn't have the ability to generate a warrior
    if ( idx_ < 0 ) { return nullptr; }

    // Only record the last warrior after it's generated.
    idx = idx_;
    // Yes, get the info of the warrior.
    int idx_global = W_n[ idx ]; // Global warrior enum idx.
    size_t warrior_m = M[ idx_global ];
    const char *color_name = COLOR_NAMES[ c ];
    const char *warrior_name = WARRIOR_NAMES[ idx_global ].c_str();

    // Reduce total life points.
    m -= warrior_m;
    // Output the production text.
    // "%s:00 %s %s %d born\n
    std::cout << stringFormat(
        OUTPUT_FORMAT,
        t, // timestamp
        color_name,
        warrior_name,
        ++n // Number
    );
    // Generate the warrior instance and return to the game coordinator.
    return getWarrior(
        static_cast<Warrior_enum>( idx_global ),
        warrior_m, P[ idx_global ], n, m
    );
}

void Commander::report( const char* t ) const {
    if ( is_occupied ) return;

    std::cout << stringFormat(
        "%s:50 %d elements in %s headquarter\n",
        t,
        m,
        COLOR_NAMES[ c ]
    );
}

class City {
    const static char* MATCH_OUTPUT_FORMAT;
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

    void moveForwardRed( City* c_, const char* t_ );

    /**
     * Blue warriors march forward, from this city to c_
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
};

// -------------------------------------------------------
// class City
// -------------------------------------------------------

const char* City::MATCH_OUTPUT_FORMAT = "%s:10 %s %s %ld marched to city %ld with %ld elements and force %ld\n";
const char* City::ROB_OUTPUT_FORMAT = "%s:35 %s %s %ld took %ld %s from %s %s %ld in city %ld\n";
const char* City::BATTLE_ONE_DEAD_OUTPUT_FORMAT = "%s:40 %s %s %ld killed %s %s %ld in city %ld remaining %ld elements\n";
const char* City::BATTLE_BOTH_DEAD_OUTPUT_FORMAT = "%s:40 both %s %s %ld and %s %s %ld died in city %ld\n";
const char* City::BATTLE_BOTH_ALIVE_OUTPUT_FORMAT = "%s:40 both %s %s %ld and %s %s %ld were alive in city %ld\n";
const char* City::OCCUPATION_OUTPUT_FORMAT = "%s:10 %s headquarter was taken\n";

bool City::canAttack() {
    assert( r != nullptr && b != nullptr );

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

void City::moveForwardRed( City* c_, const char* t_ ) {
    if ( r == nullptr ) return;
    assert( c_->r == nullptr );

    // Move the red warrior from i to i + 1;
    c_->r = r;
    // The actions that the red warrior may perform when moving forward.
    r->move();
    // Output marching info.
    std::cout << stringFormat(
        MATCH_OUTPUT_FORMAT,
        t_,
        COLOR_NAMES[ red ],
        r->getName(),
        r->id,
        c_->id,
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
    std::cout << stringFormat(
        MATCH_OUTPUT_FORMAT,
        t_,
        COLOR_NAMES[ blue ],
        b->getName(),
        b->id,
        c_->id,
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

void City::notifyOccupied( const char* t ) {
    assert( c != nullptr );

    // Store the warrior arriving the headquarters into a queue,
    // and report it as occupied.
    if ( c->c == red ) {
        // First time of being occupied, output the info.
        if ( !c->IsOccupied() )
            std::cout << stringFormat(
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

        if ( !c->IsOccupied() )
            std::cout << stringFormat(
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

// -------------------------------------------------------
// class definition
// -------------------------------------------------------

// -------------------------------------------------------
// Game class
// -------------------------------------------------------

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
        for ( size_t i = 0; i < MAX_CITY_NUM + 2; i++ ) {
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

std::pair<std::ifstream*, std::ofstream*> debuggingSetting( bool isDebug, size_t fileIdx, bool isRedirectCout );

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller( bool isDebug, size_t fileIdx, bool isRedirectCout );

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

bool WorldOfWarcraft::hasTime( int t ) const {
    // This conditional statement also includes the situation
    // where the t == 0, i.e. the game finishes as soon as each commander generates a warrior.
    return t - ( int ) c * 60 >= 0;
}

void WorldOfWarcraft::setUp( size_t n_ ) {
    c = 0; // Time starting at 000:00
    n = n_; // Number of cities excluding 0 and N + 1
    // Set id for the city N + 1.
    C[ MAX_CITY_NUM + 1 ]->setId( n + 1 );
    // Move city N + 1 to the last one which is n + 1
    std::swap( C[ n + 1 ], C[ MAX_CITY_NUM + 1 ] );
}

void WorldOfWarcraft::cleanUp() {
    // Clean up resources for each city.
    for ( size_t i = 0; i < n + 2; i++ ) {
        assert( i != 0 or i != n - 1 or C[ i ]->getCommander() != nullptr );
        C[ i ]->cleanUp();
    }
    // Move city N + 1 to the last one which is N + 1.
    std::swap( C[ n + 1 ], C[ MAX_CITY_NUM + 1 ] );
    // Set id for the city N + 1.
    C[ MAX_CITY_NUM + 1 ]->setId( MAX_CITY_NUM + 1 );
}

void WorldOfWarcraft::lionEscaping( int t_, const char* t_str ) {
    if ( t_ < 0 ) return;

    // Lion-escaping may happen in city 0 and city N + 1
    // when a lion with loyalty <= 0 in the beginning.
    for ( size_t i = 0; i < n + 2; i++ ) {
        C[ i ]->lionEscaping( t_str );
    }
}

void WorldOfWarcraft::moveForward( int t, const char* t_str ) {
    if ( t < 0 ) return;

    // Events happening at the same time, report them from east to west,
    // so move blue warriors first, then red warriors.
    // Don't forget city 0 and N + 1.
    for ( size_t i = 0; i < n + 1; i++ ) {
        // Start from east to west.
        // i.e. move a blue warrior at city i to i - 1.
        C[ i + 1 ]->moveForwardBlue( C[ i ], t_str );
    }

    for ( int i = n + 1; i > 0; i-- ) {
        // Start from west to east.
        // i.e. move a red warrior at city i to i + 1
        C[ i - 1 ]->moveForwardRed( C[ i ], t_str );
    }
}

void WorldOfWarcraft::wolfRobbing( int t, const char* t_str ) {
    if ( t < 0 ) return;

    for ( size_t i = 1; i < n + 1; i++ ) {
        C[ i ]->wolfRobbing( t_str );
    }
}

void WorldOfWarcraft::startBattle( int t, const char* t_str ) {
    if ( t < 0 ) return;

    for ( size_t i = 1; i < n + 1; i++ ) {
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
        for ( size_t i = 1; i < n + 1; i++ ) {
            C[ i ]->report( t_str );
        }
    }
}

void WorldOfWarcraft::start(
    size_t m_, size_t n_, size_t k_, int t_,
    const size_t* M_, const size_t* P_
) {
    // Wow game resource initialization
    setUp( n_ );
    // Commander initialization.
    comm_red.initResource( m_, k_, M_, P_ );
    comm_blue.initResource( m_, k_, M_, P_ );

    // Start the game.
    const char* s = nullptr;
    while ( hasTime( t_ ) ) {
        // https://en.cppreference.com/w/cpp/string/basic_string/c_str
        std::string t_str = getTimeStr( c ); // Avoid the string to be destroyed.
        s = t_str.c_str();

        // XXX:00 - generate a warrior by consuming life points.
        // Each headquarter generates a warrior if possible.
        // and report the warriors it generates.
        Warrior* w_red = comm_red.generate( s );
        if ( w_red ) { l.debug( w_red->print().c_str() ); }
        Warrior* w_blue = comm_blue.generate( s );
        if ( w_blue ) { l.debug( w_blue->print().c_str() ); }

        // Add warriors to the two cities, city 0 and n + 1.
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
    cleanUp();
}

// -------------------------------------------------------
// Helper functions
// -------------------------------------------------------

std::pair<std::ifstream*, std::ofstream*> debuggingSetting(
    bool isDebug, size_t fileIdx, bool isRedirectCout )
{
    if ( !isDebug ) return std::pair<std::ifstream*, std::ofstream*>( nullptr, nullptr );

    const size_t N = 4;
    const char* TEST_PATHS[ N ] = {
        "/home/sora/perking_cpp/final/tests/in_war_1", // Example test case on the website.
        "/home/sora/perking_cpp/final/tests/in_war_2", // 3.1) Not enough life points to generate any warriors.
        "/home/sora/perking_cpp/final/tests/in_war_3", // 3.4) t = 0
        "/home/sora/perking_cpp/final/tests/in_war_4", // Test_1
    };
    assert( fileIdx < 4 );

    // Debugging setting
    std::ifstream* fi = new std::ifstream( TEST_PATHS[ fileIdx ] );
    std::cin.rdbuf( fi->rdbuf() );
    std::ofstream* fo = new std::ofstream(
        "/home/sora/perking_cpp/final/tests/out_war_" + std::to_string( fileIdx + 1 )
    );
    if ( isRedirectCout ) std::cout.rdbuf( fo->rdbuf() );

    return std::pair<std::ifstream*, std::ofstream*>( fi, fo );
}

// -------------------------------------------------------
// Entry function
// -------------------------------------------------------

void caller( bool isDebug, size_t file_idx, bool isRedirectCout ) {
    auto p = debuggingSetting( isDebug, file_idx, isRedirectCout );

    size_t c; // Number of test cases.
    size_t m; // Total life points.
    size_t n; // Number of cities.
    size_t k; // Loyalty consumption points
    size_t t; // Time
    size_t M[ WARRIOR_NUM ]; // Life points.
    size_t P[ WARRIOR_NUM ]; // Power points.
    WorldOfWarcraft wow = WorldOfWarcraft( isDebug ? DEBUG : INFO ); // Game coordinator

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

    if ( isDebug ) {
        p.first->close();
        delete p.first;
        p.second->close();
        delete p.second;
    }
}

int main() {
    // Test cases
//    ninjiaBomb();
//    linoEscape();
//    icemanDie();
//    battleNoWeapons();
//    test2();
//    test3();

    // Game starter
    caller( false, 4, false );

    return 0;
}