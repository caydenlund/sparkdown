// src/lexer/lexers/arrow/arrow.test.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
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
TEST(ArrowLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::lexers::Arrow arrow(&state);
    arrow = mark_sideways::lexers::Arrow(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single right arrow.
TEST(ArrowLexer, SimpleArrow)
{
    mark_sideways::State state;
    mark_sideways::lexers::Arrow arrow(&state);

    std::string input = "->";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "->"));
    std::vector<mark_sideways::Token> actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));

    input = "==>\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "==>"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "\n"));
    actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single arrow with surrounding whitespace.
TEST(ArrowLexer, SingleArrowWhitespace)
{
    mark_sideways::State state;
    mark_sideways::lexers::Arrow arrow(&state);

    std::string input = "  ->  ";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "  "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "->"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "  "));
    std::vector<mark_sideways::Token> actual = arrow.lex(input);

    input = "    ==>    \n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "==>"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    \n"));
    actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles multiple arrows.
TEST(ArrowLexer, MultipleArrows)
{
    mark_sideways::State state;
    mark_sideways::lexers::Arrow arrow(&state);

    std::string input = "->->->";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "->"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "->"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "->"));
    std::vector<mark_sideways::Token> actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));

    input = "==> -> ==>\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "==>"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, " "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "->"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, " "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "==>"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "\n"));
    actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles multiple kinds of arrows.
TEST(ArrowLexer, MultipleArrowsDifferent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Arrow arrow(&state);

    std::string input = "<- -> ==> <->";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "<-"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, " "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "->"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, " "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "==>"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, " "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ARROW, "<->"));
    std::vector<mark_sideways::Token> actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly ignores escaped arrows.
TEST(ArrowLexer, EscapedArrow)
{
    mark_sideways::State state;
    mark_sideways::lexers::Arrow arrow(&state);

    std::string input = "\\->";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "->"));
    std::vector<mark_sideways::Token> actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));

    input = "\\==>";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "==>"));
    actual = arrow.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}
