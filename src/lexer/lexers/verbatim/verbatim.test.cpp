// //lexer/lexers/verbatim:verbatim.test
// v. 0.1.3
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Verbatim lexer class.
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

// The Verbatim class.
#include "lexer/lexers/verbatim/verbatim.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(VerbatimLexer, ConstructorNoFail)
{
    sparkdown::State state;
    sparkdown::lexers::Verbatim verbatim(&state);
    verbatim = sparkdown::lexers::Verbatim(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verbatim command.
TEST(VerbatimLexer, StartVerbatim)
{
    sparkdown::State state;
    sparkdown::lexers::Verbatim verbatim(&state);

    std::string input = "```";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verbatim command with a trailing newline.
TEST(VerbatimLexer, StartVerbatimNewline)
{
    sparkdown::State state;
    sparkdown::lexers::Verbatim verbatim(&state);

    std::string input = "```\n";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verbatim command with leading whitespace.
TEST(VerbatimLexer, StartVerbatimLeadingWhitespace)
{
    sparkdown::State state;
    sparkdown::lexers::Verbatim verbatim(&state);

    std::string input = "   ```";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly starts and ends a verbatim block.
TEST(VerbatimLexer, StartEndVerbatim)
{
    sparkdown::State state;
    sparkdown::lexers::Verbatim verbatim(&state);

    std::string input = "```";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "```";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "End"));
    actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly leaves text inside the verbatim block unaltered.
TEST(VerbatimLexer, TextInsideVerbatim)
{
    sparkdown::State state;
    sparkdown::lexers::Verbatim verbatim(&state);

    std::string input = "```\n";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "    Text with leading whitespace.\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "    Text with leading whitespace.\n"));
    actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "```\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "End"));
    actual = verbatim.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}
