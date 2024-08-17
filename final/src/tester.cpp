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

    delete n;
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
    rc.initResource( 0, 0, nullptr, nullptr );
    Commander bc( blue, nullptr, l );
    bc.initResource( 0, 0, nullptr, nullptr );

    City c1( 0, &rc, l );
    City c2( 1, nullptr, l );
    City c3( 2, &bc, l );

    Warrior* r = nullptr;
    Warrior* b = nullptr;
    // 000 ----------------------------------->
    const char* t_0 = "000";
    // 000:00
    r = new Wolf( 30, 18, 1, l );
    b = new Dragon( 5, 10, 1, 25, l );

    c1.setRedWarrior( r );
    c3.setBlueWarrior( b );

    c2.lionEscaping( t_0 );

    // 000:10
    c1.moveForwardRed( &c2, t_0 );
    c3.moveForwardBlue( &c2, t_0 );

    // 000:35
    c2.wolfRobbing( t_0 );

    // 000:40
    c2.startBattle( t_0 );

    // 000:55
    c2.report( t_0 );

    // 001 ----------------------------------->
    const char* t_1 = "001";
    // 001:00
    b = new Ninjia( 10, 12,  2, l );

    c3.setBlueWarrior( b );

    c2.lionEscaping( t_1 );

    // 001:10
    c3.moveForwardBlue( &c2, t_1 );

    // 001:35
    c2.wolfRobbing( t_1 );

    // 001:40
    c2.setToggleAttackingOrder( true );
    c2.startBattle( t_1 );
    c2.setToggleAttackingOrder( false );

    // 001:55
    c2.report( t_1 );

    // 002 ----------------------------------->
    const char* t_2 = "002";

    c2.lionEscaping( t_2 );

    // 002:10
    c1.moveForwardRed( &c2, t_2 );
    c2.moveForwardRed( &c3, t_2 );
    c3.moveForwardBlue( &c2, t_2 );
    c2.moveForwardBlue( &c1, t_2 );

    c2.wolfRobbing( t_2 );

    c2.startBattle( t_2 );

    // 002:50
    rc.report( t_2 );
    bc.report( t_2 );

    // 002:55
    c2.report( t_2 );
}

void test3() {
    Logger l( DEBUG );

    Commander rc( red, nullptr, l );
    rc.initResource( 0, 0, nullptr, nullptr );
    Commander bc( blue, nullptr, l );
    bc.initResource( 0, 0, nullptr, nullptr );

    City c1( 0, &rc, l );
    City c2( 1, nullptr, l );
    City c3( 2, nullptr, l );
    City c4( 3, nullptr, l );
    City c5( 4, &bc, l );

    Warrior* r = nullptr;
    Warrior* b = nullptr;
    // 000 ----------------------------------->
    const char* t_0 = "000";
    // 000:00
    r = new Lion( 20, 16, 1, 60, 0, l );
    b = new Lion( 20, 16, 1, 10, 0, l );

    c1.setRedWarrior( r );
    c5.setBlueWarrior( b );

    c2.lionEscaping( t_0 );
    c3.lionEscaping( t_0 );
    c4.lionEscaping( t_0 );

    // 000:10
    c4.moveForwardRed( &c5, t_0 );
    c3.moveForwardRed( &c4, t_0 );
    c2.moveForwardRed( &c3, t_0 );
    c1.moveForwardRed( &c2, t_0 );
    c2.moveForwardBlue( &c1, t_0 );
    c3.moveForwardBlue( &c2, t_0 );
    c4.moveForwardBlue( &c3, t_0 );
    c5.moveForwardBlue( &c4, t_0 );

    // 001 ----------------------------------->
    const char* t_1 = "001";
    // 001:00
    r = new Wolf( 30, 18, 2, l );

    r->addWeapon( new Bomb() );
    r->addWeapon( new Sword() );
    r->addWeapon( new Arrow() );
    r->addWeapon( new Sword() );

    c1.setRedWarrior( r );

    // 001:10
    c4.moveForwardRed( &c5, t_1 );
    c3.moveForwardRed( &c4, t_1 );
    c2.moveForwardRed( &c3, t_1 );
    c1.moveForwardRed( &c2, t_1 );
    c2.moveForwardBlue( &c1, t_1 );
    c3.moveForwardBlue( &c2, t_1 );
    c4.moveForwardBlue( &c3, t_1 );
    c5.moveForwardBlue( &c4, t_1 );

    // 001:35
    c2.wolfRobbing( t_1 );
    c3.wolfRobbing( t_1 );
    c4.wolfRobbing( t_1 );

    // 001:40
    c2.startBattle( t_1 );
    c3.startBattle( t_1 );
    c4.startBattle( t_1 );

    b = c3.getBlueWarrior();
    assert( b != nullptr );
    Weapon* a = new Arrow();
    a->consume();
    b->addWeapon( a );

    // 001:55
    c2.report( t_1 );
    c3.report( t_1 );
    c4.report( t_1 );

    // 002 ----------------------------------->
    const char* t_2 = "002";

    r = new Dragon( 1, 10, 3, 5, l );

    c1.setRedWarrior( r );

    c2.lionEscaping( t_2 );
    c3.lionEscaping( t_2 );
    c4.lionEscaping( t_2 );

    // 002:10
    c4.moveForwardRed( &c5, t_2 );
    c3.moveForwardRed( &c4, t_2 );
    c2.moveForwardBlue( &c1, t_2 );
    c3.moveForwardBlue( &c2, t_2 );
    c4.moveForwardBlue( &c3, t_2 );
    c5.moveForwardBlue( &c4, t_2 );

    // 002:35
    c2.wolfRobbing( t_2 );
    c3.wolfRobbing( t_2 );
    c4.wolfRobbing( t_2 );

    b = c2.getBlueWarrior();
    assert( b != nullptr );
    b->addWeapon( new Arrow() );
    b->heal( 10 );

    // 002:40
    c2.startBattle( t_2 );
    c3.startBattle( t_2 );
    c4.startBattle( t_2 );

    // 002:55
    c2.report( t_2 );
    c3.report( t_2 );
    c4.report( t_2 );

    // 003 ----------------------------------->
    const char* t_3 = "003";

    b = new Lion( 1, 26, 1, 10, 0, l );
    c2.setBlueWarrior( b );

    // 003:10
    c4.moveForwardRed( &c5, t_3 );
    c3.moveForwardRed( &c4, t_3 );
    c2.moveForwardRed( &c3, t_3 );
    c1.moveForwardRed( &c2, t_3 );

    // 003:35
    c2.wolfRobbing( t_3 );
    c3.wolfRobbing( t_3 );
    c4.wolfRobbing( t_3 );

    c2.setToggleAttackingOrder( true );
    // 002:40
    c2.startBattle( t_3 );
    c3.startBattle( t_3 );
    c4.startBattle( t_3 );
    c2.setToggleAttackingOrder( false );

    // 003:50
    rc.report( t_3 );
    bc.report( t_3 );

    // 003:55
    c2.report( t_3 );
    c3.report( t_3 );
    c4.report( t_3 );
}