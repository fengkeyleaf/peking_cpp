/*
 * tester.h
 *
 * C++ version: C++17
 *
 * Version:
 *     $1.0$
 *
 * Revisions:
 *     $1.0 basic operations on 8/3/2024
 */

#include "./wow_war.h"

/**
 *
 * @author Xiaoyu Tongyang, or call me sora for short
 * @see <a href="https://fengkeyleaf.com">person website</a>
 * @since 1.0
 */

#ifndef FINAL_TESTER_H
#define FINAL_TESTER_H

// Helpful resources ------------------------>
// Valgrind memcheck
// https://web.stanford.edu/class/archive/cs/cs107/cs107.1174/guide_valgrind.html
// https://www.jetbrains.com/help/clion/memory-profiling-with-valgrind.html

// Testing guideline ------------------------>
// 1) General warrior test
// warrior v.s. x
// warrior v.s. x and y
// warrior v.s. x and y and z
// Use each type of the weapon at least once.
// Warrior life status:
// Win, dead, tie(Both die or live)
// Warrior moving status:
// Move forward one step to an intermediate city or a city with the headquarters.
// 2) Specific warrior test
// Generate each type of warrior at least once.
// 2.1) Dragon yells
// 2.2) ninjia can use bomb without being self-damaged
// 2.3) iceman's m - 10% when going one step forward.
// 2.4) lion's loyalty -  K when going one step forward. Escape when loyalty <= 0.
// 2.5) wolf robs before a battle starts.
// 2.6) lion escapes;
// 2.7) iceman dies after moving forward.
// 3) Corner cases
// Input data category
// 3.1) Not enough life points to generate any warriors.
// 3.2) n = 1, i.e three cities in total
// 3.3) k = 0
// 3.4) t = 0
// Other categories
// 3.5) Weapon library is full, so cannot rob.
// 3.6) Battle between two warriors without any weapons available.
// 3.7) Rob by taking intact arrows first. ( Number of enemies > 3, 5 is the best )

// -------------------------------------------------------
// Other test cases
// -------------------------------------------------------

// 2.2) ninjia can use bomb without being self-damaged
void ninjiaBomb();

// 2.6) lion escapes;
void linoEscape();

// 2.7) iceman dies after moving forward.
void icemanDie();

// 3.1) Not enough life points to generate any warriors.
// See test file: in_war_2

// 3.4) t = 0
// See test file: in_war_3

// 3.6) Battle between two warriors without any weapons available.
void battleNoWeapons();

// -------------------------------------------------------
// General test cases
// -------------------------------------------------------

// Test_1
// See test file: in_war_4

// Test_2
void test2();

// Test_3
void test3();

// -------------------------------------------------------
// Test cases from the online judger
// -------------------------------------------------------

#endif //FINAL_TESTER_H
