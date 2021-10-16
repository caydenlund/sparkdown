// src/lexer/lexers/italic/italic.test.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Italic lexer class.
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

// The Italic class.
#include "lexer/lexers/italic/italic.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(ItalicLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::lexers::Italic italic(&state);
    italic = mark_sideways::lexers::Italic(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single italic token.
TEST(ItalicLexer, SimpleItalic)
{
    mark_sideways::State state;
    mark_sideways::lexers::Italic italic(&state);

    std::string input = "*Italic text.*";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "Italic text."));
    std::vector<mark_sideways::Token> actual = italic.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input += "\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "Italic text."));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "\n"));
    actual = italic.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single italic with surrounding whitespace.
TEST(ItalicLexer, SingleItalicWhitespace)
{
    mark_sideways::State state;
    mark_sideways::lexers::Italic italic(&state);

    std::string input = "  *Italic text.*  ";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "  "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "Italic text."));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "  "));
    std::vector<mark_sideways::Token> actual = italic.lex(input);

    input = "    *Italic text.*    \n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "Italic text."));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "    \n"));
    actual = italic.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles multiple italics.
TEST(ItalicLexer, MultipleItalics)
{
    mark_sideways::State state;
    mark_sideways::lexers::Italic italic(&state);

    std::string input = "*1**2**3*";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "1"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "2"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "3"));
    std::vector<mark_sideways::Token> actual = italic.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input = "*1* *2* *3*\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "1"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, " "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "2"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, " "));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, "3"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "\n"));
    actual = italic.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly ignores escaped italics.
TEST(ItalicLexer, EscapedItalic)
{
    mark_sideways::State state;
    mark_sideways::lexers::Italic italic(&state);

    std::string input = "\\*";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "*"));
    std::vector<mark_sideways::Token> actual = italic.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    input = "\\*Regular text.*";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "*"));
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "Regular text.*"));
    actual = italic.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}
