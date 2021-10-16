// src/lexer/lexers/verbatim/verbatim.test.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Verbatim lexer class.
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

// The Verbatim class.
#include "lexer/lexers/verbatim/verbatim.hpp"

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
TEST(VerbatimLexer, ConstructorNoFail)
{
    mark_sideways::State state;
    mark_sideways::lexers::Verbatim verbatim(&state);
    verbatim = mark_sideways::lexers::Verbatim(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verbatim command.
TEST(VerbatimLexer, StartVerbatim)
{
    mark_sideways::State state;
    mark_sideways::lexers::Verbatim verbatim(&state);

    std::string input = "```";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<mark_sideways::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verbatim command with a trailing newline.
TEST(VerbatimLexer, StartVerbatimNewline)
{
    mark_sideways::State state;
    mark_sideways::lexers::Verbatim verbatim(&state);

    std::string input = "```\n";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<mark_sideways::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verbatim command with leading whitespace.
TEST(VerbatimLexer, StartVerbatimLeadingWhitespace)
{
    mark_sideways::State state;
    mark_sideways::lexers::Verbatim verbatim(&state);

    std::string input = "   ```";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<mark_sideways::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly starts and ends a verbatim block.
TEST(VerbatimLexer, StartEndVerbatim)
{
    mark_sideways::State state;
    mark_sideways::lexers::Verbatim verbatim(&state);

    std::string input = "```";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<mark_sideways::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));

    input = "```";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, "End"));
    actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly leaves text inside the verbatim block unaltered.
TEST(VerbatimLexer, TextInsideVerbatim)
{
    mark_sideways::State state;
    mark_sideways::lexers::Verbatim verbatim(&state);

    std::string input = "```\n";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<mark_sideways::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));

    input = "    Text with leading whitespace.\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "    Text with leading whitespace.\n"));
    actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));

    input = "```\n";
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, "End"));
    actual = verbatim.lex(input);
    EXPECT_TRUE(tokens_equal(expected, actual));
}
