// src/lexer/lexers/enumerate/enumerate.test.cpp
// v. 0.3.2
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Enumerate lexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>
#include <vector>

// The GTest testing framework.
#include <gtest/gtest.h>

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// We use the Token class to build a vector of tokens.
#include "lexer/token/token.hpp"

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
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ENUMERATE, "1"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "List item."));
    std::vector<mark_sideways::Token> actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input = "2. List item.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ENUMERATE, "1"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "List item.\n"));
    actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single enumerate with indentation.
TEST(EnumerateLexer, LexSingleEnumerateIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    std::string input = "  1. List item.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ENUMERATE, "2"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "List item."));
    std::vector<mark_sideways::Token> actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input = "    1. List item.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ENUMERATE, "3"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "List item.\n"));
    actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles an escaped enumerate.
TEST(EnumerateLexer, LexEscapedEnumerate)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    std::string input = "\\1. List item.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "1. "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "List item."));
    std::vector<mark_sideways::Token> actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input = "    \\1. List item.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "1. "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "List item.\n"));
    actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a enumerate unmodified in math mode.
TEST(EnumerateLexer, LexEnumerateInMathMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    state.toggle_math();

    std::string input = "1. List item.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "1. List item."));
    std::vector<mark_sideways::Token> actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input = "    1. List item.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    1. List item.\n"));
    actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a enumerate unmodified in verbatim mode.
TEST(EnumerateLexer, LexEnumerateInVerbatimMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Enumerate enumerate(&state);

    state.toggle_verbatim();

    std::string input = "1. List item.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "1. List item."));
    std::vector<mark_sideways::Token> actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input = "    1. List item.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    1. List item.\n"));
    actual = enumerate.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}
