// //lexer:lexer.test
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the lex() method.
// This method is used to lex a line for parsing.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <vector>

// The GTest testing framework.
#include <gtest/gtest.h>

// We use the Token class to build a vector of tokens.
#include "token/token.hpp"

// The header for the lex() method.
#include "lexer.hpp"

using namespace sparkdown;

// Test the lex() method.
// Ensure that the method returns an empty vector when given an empty string.
TEST(Lexer, Empty)
{
    std::string input = "";

    std::vector<Token> expected;

    std::vector<Token> actual = lex(input);

    EXPECT_TRUE(Token::tokens_equal(expected, actual));

    input += "\n";

    actual = lex(input);

    EXPECT_TRUE(Token::tokens_equal(expected, actual));
}

// Test the lex() method.
// Ensure that the method returns a vector of the given terminal tokens.
TEST(Lexer, Terminal)
{
    std::string input = "abc";

    std::vector<Token> expected;
    expected.push_back(Token(token_type::TERMINAL, "abc"));

    std::vector<Token> actual = lex(input);

    EXPECT_TRUE(Token::tokens_equal(expected, actual));
}

// Test the lex() method.
// Ensure that the method can correctly lex mixed numbers and letters.
TEST(Lexer, Mixed)
{
    std::string input = "a1b2c3";

    std::vector<Token> expected;
    expected.push_back(Token(token_type::TERMINAL, 'a'));
    expected.push_back(Token(token_type::NUMBER, '1'));
    expected.push_back(Token(token_type::TERMINAL, 'b'));
    expected.push_back(Token(token_type::NUMBER, '2'));
    expected.push_back(Token(token_type::TERMINAL, 'c'));
    expected.push_back(Token(token_type::NUMBER, '3'));

    std::vector<Token> actual = lex(input);
}

// Test the lex() method.
// Ensure that the method can correctly lex each of the given spaces.
TEST(Lexer, Spaces)
{
    std::string input = " \t";

    std::vector<Token> expected;
    expected.push_back(Token(token_type::SPACE, " \t"));

    std::vector<Token> actual = lex(input);

    EXPECT_TRUE(Token::tokens_equal(expected, actual));
}

// Test the lex() method.
// Ensure that the method can correctly lex each of the given non-terminals.
TEST(Lexer, NonTerminal)
{
    std::string input = "$:[]#*-=<>\\";

    std::vector<Token> expected;
    expected.push_back(Token(token_type::DOLLAR));
    expected.push_back(Token(token_type::COLON));
    expected.push_back(Token(token_type::LBRAC));
    expected.push_back(Token(token_type::RBRAC));
    expected.push_back(Token(token_type::HASH));
    expected.push_back(Token(token_type::STAR));
    expected.push_back(Token(token_type::DASH));
    expected.push_back(Token(token_type::EQUALS));
    expected.push_back(Token(token_type::LT));
    expected.push_back(Token(token_type::GT));
    expected.push_back(Token(token_type::ESCAPE));

    std::vector<Token> actual = lex(input);

    EXPECT_TRUE(Token::tokens_equal(expected, actual));
}
