// src/lexer/lexers/itemize/itemize.test.cpp
// v. 0.3.1
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Itemize Lexer class.
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

// The Itemize class.
#include "lexer/lexers/itemize/itemize.hpp"

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
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "1"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Bullet point."));
    std::vector<mark_sideways::Token> actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));

    input = "- Bullet point.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "1"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Bullet point.\n"));
    actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bullet with indentation.
TEST(ItemizeLexer, LexSingleBulletIndent)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    std::string input = "  * Bullet point.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "2"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Bullet point."));
    std::vector<mark_sideways::Token> actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));

    input = "    - Bullet point.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "3"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Bullet point.\n"));
    actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles an escaped bullet.
TEST(ItemizeLexer, LexEscapedBullet)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    std::string input = "\\* Bullet point.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "* "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Bullet point."));
    std::vector<mark_sideways::Token> actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));

    input = "    \\- Bullet point.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "- "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Bullet point.\n"));
    actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in math mode.
TEST(ItemizeLexer, LexBulletInMathMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    state.toggle_math();

    std::string input = "* Bullet point.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "* Bullet point."));
    std::vector<mark_sideways::Token> actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));

    input = "    - Bullet point.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    - Bullet point.\n"));
    actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly leaves a bullet unmodified in verbatim mode.
TEST(ItemizeLexer, LexBulletInVerbatimMode)
{
    mark_sideways::State state;
    mark_sideways::lexers::Itemize itemize(&state);

    state.toggle_verbatim();

    std::string input = "* Bullet point.";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "* Bullet point."));
    std::vector<mark_sideways::Token> actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));

    input = "    - Bullet point.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    - Bullet point.\n"));
    actual = itemize.lex(input);
    ASSERT_TRUE(tokens_equal(expected, actual));
}
