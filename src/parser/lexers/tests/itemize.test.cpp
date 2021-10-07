// src/parser/lexers/tests/itemize.test.cpp
// v. 0.1.1
//
// Author: Cayden Lund
//   Date: 09/23/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Itemize Lexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <gtest/gtest.h>

#include "parser/state.hpp"
#include "parser/lexers/itemize.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(ItemizeLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);
    itemize = mark_sideways::lexers::Itemize(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bullet with no indentation.
TEST(ItemizeLexer, LexSingleBulletNoIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    std::string input = "* Bullet point.";
    std::string expected = "[%%==BULLET_1==%%] Bullet point.";
    std::string actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);

    input = "- Bullet point.\n";
    expected = "[%%==BULLET_1==%%] Bullet point.\n";
    actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bullet with indentation.
TEST(ItemizeLexer, LexSingleBulletIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    std::string input = "  * Bullet point.";
    std::string expected = "[%%==BULLET_2==%%] Bullet point.";
    std::string actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "[%%==BULLET_3==%%] Bullet point.\n";
    actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles an escaped bullet.
TEST(ItemizeLexer, LexEscapedBullet)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    std::string input = "\\* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    \\- Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in math mode.
TEST(ItemizeLexer, LexBulletInMathMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    state.toggle_math();

    std::string input = "* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in verbatim mode.
TEST(ItemizeLexer, LexBulletInVerbatimMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    state.toggle_verbatim();

    std::string input = "* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = itemize.lex(input);
    EXPECT_EQ(expected, actual);
}
