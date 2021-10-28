// //lexer/lexers/verb-block:verb-block.test
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the VerbBlock lexer class.
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

// The VerbBlock class.
#include "lexer/lexers/verb-block/verb-block.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(VerbBlockLexer, ConstructorNoFail)
{
    sparkdown::State state;
    sparkdown::lexers::VerbBlock verb_block(&state);
    verb_block = sparkdown::lexers::VerbBlock(&state);
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verb_block command.
TEST(VerbBlockLexer, StartVerbBlock)
{
    sparkdown::State state;
    sparkdown::lexers::VerbBlock verb_block(&state);

    std::string input = "```";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verb_block command with a trailing newline.
TEST(VerbBlockLexer, StartVerbBlockNewline)
{
    sparkdown::State state;
    sparkdown::lexers::VerbBlock verb_block(&state);

    std::string input = "```\n";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly handles a single verb_block command with leading whitespace.
TEST(VerbBlockLexer, StartVerbBlockLeadingWhitespace)
{
    sparkdown::State state;
    sparkdown::lexers::VerbBlock verb_block(&state);

    std::string input = "   ```";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly starts and ends a verb_block block.
TEST(VerbBlockLexer, StartEndVerbBlock)
{
    sparkdown::State state;
    sparkdown::lexers::VerbBlock verb_block(&state);

    std::string input = "```";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "```";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "End"));
    actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the lex() function.
// Ensures that the lexer correctly leaves text inside the verb_block block unaltered.
TEST(VerbBlockLexer, TextInsideVerbBlock)
{
    sparkdown::State state;
    sparkdown::lexers::VerbBlock verb_block(&state);

    std::string input = "```\n";
    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "Start"));
    std::vector<sparkdown::Token> actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "    Text with leading whitespace.\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, "    Text with leading whitespace.\n"));
    actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    input = "```\n";
    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::VERB_BLOCK, "End"));
    actual = verb_block.lex(input);
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}
