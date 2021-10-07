// src/lexer/lexers/enumerate/enumerate.test.cpp
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/06/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Enumerate lexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// The GTest testing framework.
#include <gtest/gtest.h>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

// The Enumerate lexer class.
#include "enumerate.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(EnumerateLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);
    enumerate = mark_sideways::lexers::Enumerate(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single enumerate with no indentation.
TEST(EnumerateLexer, LexSingleEnumerateNoIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    std::string input = "1. List item.";
    std::string expected = "[%%ENUMERATE=1%%] List item.";
    std::string actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);

    input = "2. List item.\n";
    expected = "[%%ENUMERATE=1%%] List item.\n";
    actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single enumerate with indentation.
TEST(EnumerateLexer, LexSingleEnumerateIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    std::string input = "  1. List item.";
    std::string expected = "[%%ENUMERATE=2%%] List item.";
    std::string actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    1. List item.\n";
    expected = "[%%ENUMERATE=3%%] List item.\n";
    actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly handles an escaped enumerate.
TEST(EnumerateLexer, LexEscapedEnumerate)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    std::string input = "\\1. List item.";
    std::string expected = "1. List item.";
    std::string actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    \\1. List item.\n";
    expected = "    1. List item.\n";
    actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a enumerate unmodified in math mode.
TEST(EnumerateLexer, LexEnumerateInMathMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    state.toggle_math();

    std::string input = "1. List item.";
    std::string expected = "1. List item.";
    std::string actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    1. List item.\n";
    expected = "    1. List item.\n";
    actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a enumerate unmodified in verbatim mode.
TEST(EnumerateLexer, LexEnumerateInVerbatimMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    state.toggle_verbatim();

    std::string input = "1. List item.";
    std::string expected = "1. List item.";
    std::string actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);

    input = "    1. List item.\n";
    expected = "    1. List item.\n";
    actual = enumerate.lex(input);
    EXPECT_EQ(expected, actual);
}
