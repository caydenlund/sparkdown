// //lexer/lexers/text:text.test
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Text lexer class.
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

// The Text class.
#include "lexer/lexers/text/text.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(TextLexer, ConstructorNoFail)
{
    sparkdown::State state;
    sparkdown::lexers::Text text(&state);
    text = sparkdown::lexers::Text(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single line of text.
TEST(TextLexer, SimpleText)
{
    sparkdown::State state;
    sparkdown::lexers::Text text(&state);

    std::string input = "Text content.";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "Text content."));
    std::vector<sparkdown::Token> actual = text.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input += "\n";
    actual = text.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}
