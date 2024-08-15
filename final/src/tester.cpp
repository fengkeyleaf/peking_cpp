/*
 * tester.cpp
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "../include/tester.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

void ninjiaBomb() {
    Logger l( DEBUG );
    Warrior* n = new Ninjia( 10, 10, 1, l );
    Warrior* w = new Wolf( 10, 10, 1, l );
    City c( 1, nullptr, l );

    c.setRedWarrior( n );
    c.setBlueWarrior( w );
    c.startBattle( "000" );

    // ninjia is freed after the city is destroyed.
    // wolf is dead after battle and it is freed after the battle.
}

void linoEscape() {
    Logger l( DEBUG );
    // Zero initial loyalty
    Warrior* n = new Lion( 10, 10, 1, 0, 0, l );
    n->escape( "000", "red" );
    delete n;

    // Escape after moving forward.
    n = new Lion( 10, 10, 2, 5, 3, l );
    n->move();
    n->escape( "002", "red" );
    n->move();
    n->escape( "003", "red" );
    delete n;

    // k = 0
    n = new Lion( 10, 10, 3, 5, 0, l );
    n->move();
    n->move();
    n->escape( "004", "red" );
    delete n;
}

void icemanDie() {
    Logger l( DEBUG );
    // Zero initial loyalty
    Warrior* n = new Iceman( 100, 100, 1, l );
    n->move();
    // 0, 90
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 81
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 73
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 66
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 60
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 54
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 49
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 45
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 41
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 37
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 34
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 31
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
    n->move();
    // 0, 28
    printf( "isDead: %d, m: %ld\n", n->isDead(), n->getLifePoints() );
}

void battleNoWeapons() {
    Logger l( DEBUG );

    // 1) Two wolves
    std::cout << "Two wolves--------------------------" << std::endl;
    Warrior* r = new Wolf( 10, 10, 1, l );
    Warrior* b = new Wolf( 10, 10, 1, l );
    City* c = new City( 1, nullptr, l );

    c->setRedWarrior( r );
    c->setBlueWarrior( b );
    c->wolfRobbing( "000" );
    c->startBattle( "000" );

    delete c;

    std::cout << "Two warriors--------------------------" << std::endl;
    // 2) Two warriors besides wolf
    r = new Dragon( 10, 10, 2, 20, l );
    r->discardAllWeapons();
    b = new Lion( 10, 5, 2, 10, 5, l );
    b->discardAllWeapons();
    c = new City( 2, nullptr, l );

    c->setRedWarrior( r );
    c->setBlueWarrior( b );
    c->wolfRobbing( "001" );
    c->startBattle( "001" );

    delete c;

    std::cout << "Wolf v.s. warrior--------------------------" << std::endl;
    // 3) One wolf v.s. one warrior except for wolf without weapons
    r = new Ninjia( 10, 10, 3, l );
    r->discardAllWeapons();
    b = new Wolf( 10, 5, 3, l );
    b->discardAllWeapons();
    c = new City( 3, nullptr, l );

    c->setRedWarrior( r );
    c->setBlueWarrior( b );
    c->wolfRobbing( "002" );
    c->startBattle( "002" );

    delete c;
}

void test2() {
    Logger l( DEBUG );

    Commander rc( red, nullptr, l );
    Commander bc( blue, nullptr, l );

    City c1( 0, &rc, l );
    City c2( 1, nullptr, l );
    City c3( 2, &bc, l );

    Warrior* r = nullptr;
    Warrior* b = nullptr;
    // 000 ----------------------------------->
    // 000:00
    const char* t_0 = "000";
    r = new Wolf( 30, 18, 1, l );
    b = new Dragon( 5, 10, 1, 25, l );

    c1.setRedWarrior( r );
    c3.setBlueWarrior( b );

    c2.lionEscaping( t_0 );

    // 000:10
    c1.moveForwardRed( &c2, t_0 );
    c3.moveForwardBlue( &c2, t_0 );

    c2.wolfRobbing( t_0 );

    // 000:35
    c2.startBattle( t_0 );

    // 000:55
    c2.report( t_0 );

    // 001 ----------------------------------->
    // 001:00
    const char* t_1 = "001";
}

void test3() {

}