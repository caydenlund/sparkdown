// src/parser/lexers/tests/bullets.test.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 09/23/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Bullets Lexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <gtest/gtest.h>

#include "parser/state.hpp"
#include "parser/lexers/bullets.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(BulletsLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::lexers::Bullets bullets(&state);
    bullets = mark_sideways::lexers::Bullets(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bullet with no indentation.
TEST(BulletsLexer, LexSingleBulletNoIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Bullets bullets(&state);

    std::string input = "* Bullet point.";
    std::string expected = "[%%==BULLET_1==%%] Bullet point.";
    std::string actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);

    input = "- Bullet point.\n";
    expected = "[%%==BULLET_1==%%] Bullet point.\n";
    actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bullet with indentation.
TEST(BulletsLexer, LexSingleBulletIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Bullets bullets(&state);

    std::string input = "  * Bullet point.";
    std::string expected = "[%%==BULLET_2==%%] Bullet point.";
    std::string actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "[%%==BULLET_3==%%] Bullet point.\n";
    actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles an escaped bullet.
TEST(BulletsLexer, LexEscapedBullet)
{
    mark_sideways::State state;
    mark_sideways::lexers::Bullets bullets(&state);

    std::string input = "\\* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    \\- Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in math mode.
TEST(BulletsLexer, LexBulletInMathMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Bullets bullets(&state);

    state.toggle_math();

    std::string input = "* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in verbatim mode.
TEST(BulletsLexer, LexBulletInVerbatimMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Bullets bullets(&state);

    state.toggle_verbatim();

    std::string input = "* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = bullets.lex(input);
    EXPECT_EQ(expected, actual);
}
