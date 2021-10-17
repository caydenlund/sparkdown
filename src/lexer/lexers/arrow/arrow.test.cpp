// src/lexer/lexers/arrow/arrow.test.cpp
// v. 0.1.2
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Arrow lexer class.
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

// The Arrow class.
#include "lexer/lexers/arrow/arrow.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(ArrowLexer, ConstructorNoFail)
{
    sparkdown::State state;
    sparkdown::lexers::Arrow arrow(&state);
    arrow = sparkdown::lexers::Arrow(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single right arrow.
TEST(ArrowLexer, SimpleArrow)
{
    sparkdown::State state;
    sparkdown::lexers::Arrow arrow(&state);

    std::string input = "->";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));
    std::vector<sparkdown::Token> actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "==>\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "==>"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "\n"));
    actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single arrow with surrounding whitespace.
TEST(ArrowLexer, SingleArrowWhitespace)
{
    sparkdown::State state;
    sparkdown::lexers::Arrow arrow(&state);

    std::string input = "  ->  ";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "  "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "  "));
    std::vector<sparkdown::Token> actual = arrow.lex(input);

    input = "    ==>    \n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "    "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "==>"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "    \n"));
    actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles multiple arrows.
TEST(ArrowLexer, MultipleArrows)
{
    sparkdown::State state;
    sparkdown::lexers::Arrow arrow(&state);

    std::string input = "->->->";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));
    std::vector<sparkdown::Token> actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "==> -> ==>\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "==>"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, " "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, " "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "==>"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "\n"));
    actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles multiple kinds of arrows.
TEST(ArrowLexer, MultipleArrowsDifferent)
{
    sparkdown::State state;
    sparkdown::lexers::Arrow arrow(&state);

    std::string input = "<- -> ==> <->";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "<-"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, " "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, " "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "==>"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, " "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "<->"));
    std::vector<sparkdown::Token> actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly ignores escaped arrows.
TEST(ArrowLexer, EscapedArrow)
{
    sparkdown::State state;
    sparkdown::lexers::Arrow arrow(&state);

    std::string input = "\\->";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "->"));
    std::vector<sparkdown::Token> actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "\\==>";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "==>"));
    actual = arrow.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}
