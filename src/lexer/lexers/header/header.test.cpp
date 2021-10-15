// src/lexer/lexers/header/header.test.cpp
// v. 0.1.1
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Header lexer class.
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

// The Header class.
#include "lexer/lexers/header/header.hpp"

// We define a static helper method to determine whether two vectors of tokens are equal.
//
// * std::vector<mark_sideways::Token> tokens1 - The first vector of tokens.
// * std::vector<mark_sideways::Token> tokens2 - The second vector of tokens.
// * return bool                               - True when the two vectors are equal; false otherwise.
static bool tokens_equal(std::vector<mark_sideways::Token> tokens1, std::vector<mark_sideways::Token> tokens2)
{
    if (tokens1.size() != tokens2.size())
    {
        return false;
    }
    for (size_t i = 0; i < tokens1.size(); i++)
    {
        if (tokens1[i] != tokens2[i])
        {
            return false;
        }
    }
    return true;
}

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(HeaderLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);
    header = mark_sideways::lexers::Header(&state);
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a simple header command.
TEST(HeaderLexer, SimpleHeader)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<mark_sideways::Token> actual = header.lex("$date: 10-15-2021");
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a header command with a trailing newline.
TEST(HeaderLexer, Newline)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<mark_sideways::Token> actual = header.lex("$date: 10-15-2021\n");
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a header command with special characters.
TEST(HeaderLexer, SpecialCharacters)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::HEADER, "date=*10-15-2021*"));
    std::vector<mark_sideways::Token> actual = header.lex("$date: *10-15-2021*");
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes an escaped header command.
TEST(HeaderLexer, EscapedHeader)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "$date: 10-15-2021"));
    std::vector<mark_sideways::Token> actual = header.lex("\\$date: 10-15-2021");
    EXPECT_TRUE(tokens_equal(expected, actual));
    EXPECT_FALSE(state.is_head());
}

// Test the lexer's method lex().
// Ensures that the lexer correctly ignores header commands after state.is_head() is false.
TEST(HeaderLexer, IgnoreHeader)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);

    state.end_head();
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "$date: 10-15-2021"));
    std::vector<mark_sideways::Token> actual = header.lex("$date: 10-15-2021");
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly calls state.end_head() when we are done with the header.
TEST(HeaderLexer, EndHeader)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<mark_sideways::Token> actual = header.lex("$date: 10-15-2021\n");
    EXPECT_TRUE(tokens_equal(expected, actual));
    EXPECT_TRUE(state.is_head());

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::HEADER, "title=Title"));
    actual = header.lex("$title: Title\n");
    EXPECT_TRUE(tokens_equal(expected, actual));
    EXPECT_TRUE(state.is_head());

    header.lex("    \n");
    header.lex("    \n");
    EXPECT_TRUE(state.is_head());

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Content.\n"));
    actual = header.lex("Content.\n");
    EXPECT_TRUE(tokens_equal(expected, actual));
    EXPECT_FALSE(state.is_head());
}

// Test the lexer's method lex().
// Ensures that the lexer correctly calls state.end_head() when we come across a line of '=' characters.
TEST(HeaderLexer, EndHeaderOnEquals)
{
    mark_sideways::State state;
    mark_sideways::lexers::Header header(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<mark_sideways::Token> actual = header.lex("$date: 10-15-2021\n");
    EXPECT_TRUE(tokens_equal(expected, actual));
    EXPECT_TRUE(state.is_head());

    expected.clear();
    actual = header.lex("=======\n");
    EXPECT_TRUE(tokens_equal(expected, actual));
    EXPECT_FALSE(state.is_head());
}
