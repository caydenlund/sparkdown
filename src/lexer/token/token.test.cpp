// src/token/token.test.cpp
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Token class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// The GTest testing framework.
#include <gtest/gtest.h>

// The Token header file.
#include "token.hpp"

// Test the Token class's constructor.
// Ensure that it doesn't throw an exception.
TEST(Token, ConstructorNoFail)
{
    mark_sideways::Token token_a(mark_sideways::Token::token_type::BULLET, "1");
    mark_sideways::Token token_b(mark_sideways::Token::token_type::BULLET, "2");
    mark_sideways::Token *token_c = new mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "2");
    delete token_c;
}

// Test the Token class's method get_type().
TEST(Token, GetType)
{
    mark_sideways::Token token_a(mark_sideways::Token::token_type::BULLET, "1");

    EXPECT_EQ(mark_sideways::Token::token_type::BULLET, token_a.get_type());
}

// Test the Token class's method get_value().
TEST(Token, GetValue)
{
    mark_sideways::Token token_a(mark_sideways::Token::token_type::BULLET, "123");

    std::string expected = "123";
    std::string actual = token_a.get_value();

    EXPECT_EQ(expected, actual);
}

// Test the Token class's overloaded operator ==.
TEST(Token, OperatorEqual)
{
    mark_sideways::Token token_a(mark_sideways::Token::token_type::BULLET, "123");
    mark_sideways::Token token_b(mark_sideways::Token::token_type::BULLET, "123");

    EXPECT_TRUE(token_a == token_b);

    mark_sideways::Token token_c(mark_sideways::Token::token_type::BULLET, "1234");
    mark_sideways::Token token_d = token_c;

    EXPECT_TRUE(token_c == token_d);

    mark_sideways::Token token_e(mark_sideways::Token::token_type::BULLET, "123");
    mark_sideways::Token token_f(mark_sideways::Token::token_type::BULLET, "1234");

    EXPECT_FALSE(token_e == token_f);

    mark_sideways::Token token_g(mark_sideways::Token::token_type::BULLET, "123");
    mark_sideways::Token token_h(mark_sideways::Token::token_type::ENUMERATE, "123");

    EXPECT_FALSE(token_g == token_h);
}

// Test the Token class's overloaded operator !=.
TEST(Token, OperatorNotEqual)
{
    mark_sideways::Token token_a(mark_sideways::Token::token_type::BULLET, "123");
    mark_sideways::Token token_b(mark_sideways::Token::token_type::BULLET, "123");

    EXPECT_FALSE(token_a != token_b);

    mark_sideways::Token token_c(mark_sideways::Token::token_type::BULLET, "1234");
    mark_sideways::Token token_d = token_c;

    EXPECT_FALSE(token_c != token_d);

    mark_sideways::Token token_e(mark_sideways::Token::token_type::BULLET, "123");
    mark_sideways::Token token_f(mark_sideways::Token::token_type::BULLET, "1234");

    EXPECT_TRUE(token_e != token_f);

    mark_sideways::Token token_g(mark_sideways::Token::token_type::BULLET, "123");
    mark_sideways::Token token_h(mark_sideways::Token::token_type::ENUMERATE, "123");

    EXPECT_TRUE(token_g != token_h);
}

// Test the Token class's static method get_token_type().
TEST(Token, GetTokenType)
{
    std::string expected = "Bullet";
    std::string actual = mark_sideways::Token::get_token_type(mark_sideways::Token::token_type::BULLET);
    EXPECT_EQ(expected, actual);
}

// Test the Token class's static method tokens_equal().
TEST(Token, TokensEqual)
{
    std::vector<mark_sideways::Token> tokens_a;
    tokens_a.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "1"));
    tokens_a.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "2"));
    tokens_a.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "3"));

    std::vector<mark_sideways::Token> tokens_b;
    tokens_b.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "1"));
    tokens_b.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "2"));
    tokens_b.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "3"));

    EXPECT_TRUE(mark_sideways::Token::tokens_equal(tokens_a, tokens_b));
}

// Test the Token class's static method print_tokens().
TEST(Token, PrintTokens)
{
    std::vector<mark_sideways::Token> input;
    input.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "1"));
    input.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "2"));
    input.push_back(mark_sideways::Token(mark_sideways::Token::token_type::BULLET, "3"));

    std::stringstream expected;
    expected << "Tokens (3):" << std::endl
             << "Bullet: \"1\"" << std::endl
             << "Bullet: \"2\"" << std::endl
             << "Bullet: \"3\"" << std::endl;

    std::string actual = mark_sideways::Token::print_tokens(input);

    EXPECT_EQ(expected.str(), actual);
}
