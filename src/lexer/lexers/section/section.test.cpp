// src/lexer/lexers/section/section.test.cpp
// v. 0.1.2
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Section lexer class.
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

// The Section class.
#include "section.hpp"

// Test the constructor.
// Ensures that the lexer does not throw an exception.
TEST(SectionLexer, Constructor)
{
    sparkdown::State state;
    sparkdown::lexers::Section section(&state);
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a simple section headline.
TEST(SectionLexer, SimpleHeadline)
{
    sparkdown::State state;
    sparkdown::lexers::Section section(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=1,TITLE=Section."));
    std::vector<sparkdown::Token> actual = section.lex("# Section.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    actual = section.lex("# Section.\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the Section lexer's method lex().
// Ensures that the lexer correctly lexes a header with internal symbols.
TEST(SectionLexer, SpecialSymbols)
{
    sparkdown::State state;
    sparkdown::lexers::Section section(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=1,TITLE=Section with whitespace."));
    std::vector<sparkdown::Token> actual = section.lex("# Section with whitespace.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    actual = section.lex("# Section with whitespace.\n");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=1,TITLE=Section with *asterisks.*"));
    actual = section.lex("# Section with *asterisks.*");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=1,TITLE=Section with an arrow. ->"));
    actual = section.lex("# Section with an arrow. ->");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the Section lexer's method lex().
// Ensures that the lexer correctly lexes various levels of headlines.
TEST(SectionLexer, HeadlineLevels)
{
    sparkdown::State state;
    sparkdown::lexers::Section section(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=1,TITLE=Section."));
    std::vector<sparkdown::Token> actual = section.lex("# Section.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=2,TITLE=Subsection."));
    actual = section.lex("## Subsection.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=3,TITLE=Subsubsection."));
    actual = section.lex("### Subsubsection.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=4,TITLE=Subsubsubsection."));
    actual = section.lex("#### Subsubsubsection.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::SECTION, "LEVEL=5,TITLE=Subsubsubsubsection."));
    actual = section.lex("##### Subsubsubsubsection.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}

// Test the Section lexer's method lex().
// Ensures that the lexer correctly leaves the input string unmodified when given a string with no section headline.
TEST(SectionLexer, NoHeadline)
{
    sparkdown::State state;
    sparkdown::lexers::Section section(&state);

    std::vector<sparkdown::Token> expected;
    expected.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, "This is a paragraph."));
    std::vector<sparkdown::Token> actual = section.lex("This is a paragraph.");
    EXPECT_TRUE(sparkdown::Token::tokens_equal(expected, actual));
}
