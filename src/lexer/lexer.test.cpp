// src/lexer/lexer.test.cpp
// v. 0.2.3
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Lexer class.
// Since the Lexer class is an aggregate of all the other sub-lexers,
// the tests for individual sub-lexers are contained in the sub-lexer tests.
// The tests here are mainly for possible interactions between the sub-lexers.
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

// The Lexer class.
#include "lexer.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(Lexer, ConstructorNoFail)
{
    sparkdown::State state;
    sparkdown::Lexer *lexer = new sparkdown::Lexer(&state);
    delete lexer;
    lexer = new sparkdown::Lexer(&state);
}

// Test the Lexer class's method lex().
// Ensures that the lexer can correctly lex an indented bullet point with a single right arrow.
TEST(Lexer, BulletArrow)
{
    sparkdown::State state;
    sparkdown::Lexer lexer = sparkdown::Lexer(&state);

    std::string input = "  * Text. ->";

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BULLET, "2"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "Text. "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, "->"));

    std::vector<sparkdown::Token> actual = lexer.lex(input);

    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input += "\n";

    actual = lexer.lex(input);

    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}
