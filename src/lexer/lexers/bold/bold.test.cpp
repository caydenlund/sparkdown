// //lexer/lexers/bold:bold.test
// v. 0.1.2
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Bold lexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

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

// The Bold class.
#include "lexer/lexers/bold/bold.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(BoldLexer, ConstructorNoFail)
{
    sparkdown::State state;
    sparkdown::lexers::Bold bold(&state);
    bold = sparkdown::lexers::Bold(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bold token.
TEST(BoldLexer, SimpleBold)
{
    sparkdown::State state;
    sparkdown::lexers::Bold bold(&state);

    std::string input = "**Bold text.**";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "Bold text."));
    std::vector<sparkdown::Token> actual = bold.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input += "\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "Bold text."));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "\n"));
    actual = bold.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single bold with surrounding whitespace.
TEST(BoldLexer, SingleBoldWhitespace)
{
    sparkdown::State state;
    sparkdown::lexers::Bold bold(&state);

    std::string input = "  **Bold text.**  ";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "  "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "Bold text."));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "  "));
    std::vector<sparkdown::Token> actual = bold.lex(input);

    input = "    **Bold text.**    \n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "    "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "Bold text."));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "    \n"));
    actual = bold.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles multiple bolds.
TEST(BoldLexer, MultipleBolds)
{
    sparkdown::State state;
    sparkdown::lexers::Bold bold(&state);

    std::string input = "**1****2****3**";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "1"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "2"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "3"));
    std::vector<sparkdown::Token> actual = bold.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "**1** **2** **3**\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "1"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, " "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "2"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, " "));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::BOLD, "3"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "\n"));
    actual = bold.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly ignores escaped bolds.
TEST(BoldLexer, EscapedBold)
{
    sparkdown::State state;
    sparkdown::lexers::Bold bold(&state);

    std::string input = "\\**";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "**"));
    std::vector<sparkdown::Token> actual = bold.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "\\**Regular text.**";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "**"));
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "Regular text.**"));
    actual = bold.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}
