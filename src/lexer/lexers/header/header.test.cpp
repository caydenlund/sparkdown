// src/lexer/lexers/header/header.test.cpp
// v. 0.1.3
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
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

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(HeaderLexer, ConstructorNoFail)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);
    header = sparkdown::lexers::Header(&state);
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a simple header command.
TEST(HeaderLexer, SimpleHeader)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<sparkdown::Token> actual = header.lex("$date: 10-15-2021");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a header command with a trailing newline.
TEST(HeaderLexer, Newline)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<sparkdown::Token> actual = header.lex("$date: 10-15-2021\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a header command with special characters.
TEST(HeaderLexer, SpecialCharacters)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::HEADER, "date=*10-15-2021*"));
    std::vector<sparkdown::Token> actual = header.lex("$date: *10-15-2021*");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes an escaped header command.
TEST(HeaderLexer, EscapedHeader)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "$date: 10-15-2021"));
    std::vector<sparkdown::Token> actual = header.lex("\\$date: 10-15-2021");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
    EXPECT_FALSE(state.is_head());
}

// Test the lexer's method lex().
// Ensures that the lexer correctly ignores header commands after state.is_head() is false.
TEST(HeaderLexer, IgnoreHeader)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);

    state.end_head();
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "$date: 10-15-2021"));
    std::vector<sparkdown::Token> actual = header.lex("$date: 10-15-2021");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lexer's method lex().
// Ensures that the lexer correctly calls state.end_head() when we are done with the header.
TEST(HeaderLexer, EndHeader)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<sparkdown::Token> actual = header.lex("$date: 10-15-2021\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
    EXPECT_TRUE(state.is_head());

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::HEADER, "title=Title"));
    actual = header.lex("$title: Title\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
    EXPECT_TRUE(state.is_head());

    header.lex("    \n");
    header.lex("    \n");
    EXPECT_TRUE(state.is_head());

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "Content.\n"));
    actual = header.lex("Content.\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
    EXPECT_FALSE(state.is_head());
}

// Test the lexer's method lex().
// Ensures that the lexer correctly calls state.end_head() when we come across a line of '=' characters.
TEST(HeaderLexer, EndHeaderOnEquals)
{
    sparkdown::State state;
    sparkdown::lexers::Header header(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::HEADER, "date=10-15-2021"));
    std::vector<sparkdown::Token> actual = header.lex("$date: 10-15-2021\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
    EXPECT_TRUE(state.is_head());

    expected.clear();
    actual = header.lex("=======\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
    EXPECT_FALSE(state.is_head());
}
