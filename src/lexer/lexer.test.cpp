// src/lexer/lexer.test.cpp
// v. 0.1.1
//
// Author: Cayden Lund
//   Date: 10/06/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Lexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// The GTest testing framework.
#include <gtest/gtest.h>

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// The Lexer class.
#include "lexer.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(LexerEnumerateLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::Lexer *lexer = new mark_sideways::Lexer(&state);
    delete lexer;
    lexer = new mark_sideways::Lexer(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single enumerate with no indentation.
TEST(LexerEnumerateLexer, LexSingleEnumerateNoIndent)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    std::string input = "1. List item.";
    std::string expected = "[%%ENUMERATE=1%%] List item.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "2. List item.\n";
    expected = "[%%ENUMERATE=1%%] List item.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single enumerate with indentation.
TEST(LexerEnumerateLexer, LexSingleEnumerateIndent)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    std::string input = "  1. List item.";
    std::string expected = "[%%ENUMERATE=2%%] List item.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    1. List item.\n";
    expected = "[%%ENUMERATE=3%%] List item.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles an escaped enumerate.
TEST(LexerEnumerateLexer, LexEscapedEnumerate)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    std::string input = "\\1. List item.";
    std::string expected = "1. List item.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    \\1. List item.\n";
    expected = "    1. List item.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a enumerate unmodified in math mode.
TEST(LexerEnumerateLexer, LexEnumerateInMathMode)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    state.toggle_math();

    std::string input = "1. List item.";
    std::string expected = "1. List item.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    1. List item.\n";
    expected = "    1. List item.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a enumerate unmodified in verbatim mode.
TEST(LexerEnumerateLexer, LexEnumerateInVerbatimMode)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    state.toggle_verbatim();

    std::string input = "1. List item.";
    std::string expected = "1. List item.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    1. List item.\n";
    expected = "    1. List item.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bullet with no indentation.
TEST(LexerItemizeLexer, LexSingleBulletNoIndent)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    std::string input = "* Bullet point.";
    std::string expected = "[%%BULLET=1%%] Bullet point.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "- Bullet point.\n";
    expected = "[%%BULLET=1%%] Bullet point.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bullet with indentation.
TEST(LexerItemizeLexer, LexSingleBulletIndent)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    std::string input = "  * Bullet point.";
    std::string expected = "[%%BULLET=2%%] Bullet point.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "[%%BULLET=3%%] Bullet point.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles an escaped bullet.
TEST(LexerItemizeLexer, LexEscapedBullet)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    std::string input = "\\* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    \\- Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in math mode.
TEST(LexerItemizeLexer, LexBulletInMathMode)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    state.toggle_math();

    std::string input = "* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in verbatim mode.
TEST(LexerItemizeLexer, LexBulletInVerbatimMode)
{
    mark_sideways::State state;
    mark_sideways::Lexer lexer(&state);

    state.toggle_verbatim();

    std::string input = "* Bullet point.";
    std::string expected = "* Bullet point.";
    std::string actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    - Bullet point.\n";
    expected = "    - Bullet point.\n";
    actual = lexer.lex(input);
    EXPECT_EQ(expected, actual);
}
