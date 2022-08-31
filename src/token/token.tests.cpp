/**
 * @file token/token.tests.cpp
 * @package //token:token.tests
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `token` class unit tests.
 * @details This project is part of Sparkdown, a new markup language
 *     for quickly writing and formatting notes.
 *
 *     This file tests the `token` class, which represents a single token
 *     in the lexing/parsing process.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#include "token.hpp"

#include <gtest/gtest.h>

/**
 * @brief `token#token(char)` no-fail test.
 * @details Ensures that the constructor does not throw an exception.
 *
 *     Also, the `EXPECT_EQ` tests are to avoid compiler warnings.
 *     ("Local copy is never modified",
 *     "local copy is assigned but never accessed", etc.)
 *
 */
TEST(token, constructor_no_fail) {
    sparkdown::token token_implicit = '1';
    EXPECT_EQ(token_implicit, token_implicit);

    sparkdown::token token_explicit('1');
    EXPECT_EQ(token_explicit, token_explicit);

    sparkdown::token token_copy(token_implicit);
    EXPECT_EQ(token_copy, token_implicit);

    sparkdown::token token_assignment = token_implicit;
    EXPECT_EQ(token_assignment, token_assignment);
}

/**
 * @brief `token#token(char)` test.
 * @details Ensures that the constructor correctly identifies the type of each
 *     token, and that it correctly saves the value of each token.
 *
 *     Is essentially an integration test for the constructor and the
 *     get_value() static method.
 *
 *     . . . Wow. This would have taken forever to write by hand.
 *     vim macros make it *too* easy to generate code like this.
 *
 */
TEST(token, constructor_correct) {
    sparkdown::token space = ' ';
    EXPECT_EQ(sparkdown::token_type::SPACE, space.type);
    EXPECT_EQ(' ', space.value);

    sparkdown::token tab = '\t';
    EXPECT_EQ(sparkdown::token_type::SPACE, tab.type);
    EXPECT_EQ('\t', tab.value);

    sparkdown::token dollar = '$';
    EXPECT_EQ(sparkdown::token_type::DOLLAR, dollar.type);
    EXPECT_EQ('$', dollar.value);

    sparkdown::token colon = ':';
    EXPECT_EQ(sparkdown::token_type::COLON, colon.type);
    EXPECT_EQ(':', colon.value);

    sparkdown::token period = '.';
    EXPECT_EQ(sparkdown::token_type::PERIOD, period.type);
    EXPECT_EQ('.', period.value);

    sparkdown::token lbrac = '[';
    EXPECT_EQ(sparkdown::token_type::LBRAC, lbrac.type);
    EXPECT_EQ('[', lbrac.value);

    sparkdown::token rbrac = ']';
    EXPECT_EQ(sparkdown::token_type::RBRAC, rbrac.type);
    EXPECT_EQ(']', rbrac.value);

    sparkdown::token hash = '#';
    EXPECT_EQ(sparkdown::token_type::HASH, hash.type);
    EXPECT_EQ('#', hash.value);

    sparkdown::token star = '*';
    EXPECT_EQ(sparkdown::token_type::STAR, star.type);
    EXPECT_EQ('*', star.value);

    sparkdown::token dash = '-';
    EXPECT_EQ(sparkdown::token_type::DASH, dash.type);
    EXPECT_EQ('-', dash.value);

    sparkdown::token equals = '=';
    EXPECT_EQ(sparkdown::token_type::EQUALS, equals.type);
    EXPECT_EQ('=', equals.value);

    sparkdown::token lt = '<';
    EXPECT_EQ(sparkdown::token_type::LT, lt.type);
    EXPECT_EQ('<', lt.value);

    sparkdown::token gt = '>';
    EXPECT_EQ(sparkdown::token_type::GT, gt.type);
    EXPECT_EQ('>', gt.value);

    sparkdown::token pipe = '|';
    EXPECT_EQ(sparkdown::token_type::PIPE, pipe.type);
    EXPECT_EQ('|', pipe.value);

    sparkdown::token tick = '`';
    EXPECT_EQ(sparkdown::token_type::TICK, tick.type);
    EXPECT_EQ('`', tick.value);

    sparkdown::token escape = '\\';
    EXPECT_EQ(sparkdown::token_type::ESCAPE, escape.type);
    EXPECT_EQ('\\', escape.value);

    sparkdown::token number_0 = '0';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_0.type);
    EXPECT_EQ('0', number_0.value);

    sparkdown::token number_1 = '1';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_1.type);
    EXPECT_EQ('1', number_1.value);

    sparkdown::token number_2 = '2';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_2.type);
    EXPECT_EQ('2', number_2.value);

    sparkdown::token number_3 = '3';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_3.type);
    EXPECT_EQ('3', number_3.value);

    sparkdown::token number_4 = '4';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_4.type);
    EXPECT_EQ('4', number_4.value);

    sparkdown::token number_5 = '5';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_5.type);
    EXPECT_EQ('5', number_5.value);

    sparkdown::token number_6 = '6';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_6.type);
    EXPECT_EQ('6', number_6.value);

    sparkdown::token number_7 = '7';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_7.type);
    EXPECT_EQ('7', number_7.value);

    sparkdown::token number_8 = '8';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_8.type);
    EXPECT_EQ('8', number_8.value);

    sparkdown::token number_9 = '9';
    EXPECT_EQ(sparkdown::token_type::NUMBER, number_9.type);
    EXPECT_EQ('9', number_9.value);

    sparkdown::token other_a = 'a';
    EXPECT_EQ(sparkdown::token_type::OTHER, other_a.type);
    EXPECT_EQ('a', other_a.value);

    sparkdown::token other_A = 'A';
    EXPECT_EQ(sparkdown::token_type::OTHER, other_A.type);
    EXPECT_EQ('A', other_A.value);

    sparkdown::token other_underscore = '_';
    EXPECT_EQ(sparkdown::token_type::OTHER, other_underscore.type);
    EXPECT_EQ('_', other_underscore.value);

    sparkdown::token other_semicolon = ';';
    EXPECT_EQ(sparkdown::token_type::OTHER, other_semicolon.type);
    EXPECT_EQ(';', other_semicolon.value);
}

/**
 * @brief `token#get_value()` test.
 * @details Ensures that the constructor does not throw an exception.
 *
 */
TEST(token, get_value) {
    EXPECT_EQ(sparkdown::token_type::SPACE, sparkdown::token::get_type(' '));
    EXPECT_EQ(sparkdown::token_type::SPACE, sparkdown::token::get_type('\t'));

    EXPECT_EQ(sparkdown::token_type::DOLLAR, sparkdown::token::get_type('$'));
    EXPECT_EQ(sparkdown::token_type::COLON, sparkdown::token::get_type(':'));
    EXPECT_EQ(sparkdown::token_type::PERIOD, sparkdown::token::get_type('.'));
    EXPECT_EQ(sparkdown::token_type::LBRAC, sparkdown::token::get_type('['));
    EXPECT_EQ(sparkdown::token_type::RBRAC, sparkdown::token::get_type(']'));
    EXPECT_EQ(sparkdown::token_type::HASH, sparkdown::token::get_type('#'));
    EXPECT_EQ(sparkdown::token_type::STAR, sparkdown::token::get_type('*'));
    EXPECT_EQ(sparkdown::token_type::DASH, sparkdown::token::get_type('-'));
    EXPECT_EQ(sparkdown::token_type::EQUALS, sparkdown::token::get_type('='));
    EXPECT_EQ(sparkdown::token_type::LT, sparkdown::token::get_type('<'));
    EXPECT_EQ(sparkdown::token_type::GT, sparkdown::token::get_type('>'));
    EXPECT_EQ(sparkdown::token_type::PIPE, sparkdown::token::get_type('|'));
    EXPECT_EQ(sparkdown::token_type::TICK, sparkdown::token::get_type('`'));
    EXPECT_EQ(sparkdown::token_type::ESCAPE, sparkdown::token::get_type('\\'));

    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('0'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('1'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('2'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('3'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('4'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('5'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('6'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('7'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('8'));
    EXPECT_EQ(sparkdown::token_type::NUMBER, sparkdown::token::get_type('9'));

    EXPECT_EQ(sparkdown::token_type::OTHER, sparkdown::token::get_type('a'));
    EXPECT_EQ(sparkdown::token_type::OTHER, sparkdown::token::get_type('A'));
    EXPECT_EQ(sparkdown::token_type::OTHER, sparkdown::token::get_type('_'));
    EXPECT_EQ(sparkdown::token_type::OTHER, sparkdown::token::get_type(';'));
}

TEST(token, operator_equality) {
    EXPECT_TRUE(sparkdown::token('=') == sparkdown::token('='));
    EXPECT_TRUE(sparkdown::token('(') == sparkdown::token('('));
    EXPECT_TRUE(sparkdown::token(')') == sparkdown::token(')'));
    EXPECT_TRUE(sparkdown::token('#') == sparkdown::token('#'));
    EXPECT_TRUE(sparkdown::token('0') == sparkdown::token('0'));
    EXPECT_TRUE(sparkdown::token(' ') == sparkdown::token(' '));
    EXPECT_TRUE(sparkdown::token('a') == sparkdown::token('a'));

    EXPECT_FALSE(sparkdown::token('(') == sparkdown::token(')'));
    EXPECT_FALSE(sparkdown::token('=') == sparkdown::token('#'));
    EXPECT_FALSE(sparkdown::token(' ') == sparkdown::token('\t'));
    EXPECT_FALSE(sparkdown::token('0') == sparkdown::token('8'));
    EXPECT_FALSE(sparkdown::token('a') == sparkdown::token('A'));
}

TEST(token, operator_inequality) {
    EXPECT_FALSE(sparkdown::token('=') != sparkdown::token('='));
    EXPECT_FALSE(sparkdown::token('(') != sparkdown::token('('));
    EXPECT_FALSE(sparkdown::token(')') != sparkdown::token(')'));
    EXPECT_FALSE(sparkdown::token('#') != sparkdown::token('#'));
    EXPECT_FALSE(sparkdown::token('0') != sparkdown::token('0'));
    EXPECT_FALSE(sparkdown::token(' ') != sparkdown::token(' '));
    EXPECT_FALSE(sparkdown::token('a') != sparkdown::token('a'));

    EXPECT_TRUE(sparkdown::token('(') != sparkdown::token(')'));
    EXPECT_TRUE(sparkdown::token('=') != sparkdown::token('#'));
    EXPECT_TRUE(sparkdown::token(' ') != sparkdown::token('\t'));
    EXPECT_TRUE(sparkdown::token('0') != sparkdown::token('8'));
    EXPECT_TRUE(sparkdown::token('a') != sparkdown::token('A'));
}