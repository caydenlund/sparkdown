// src/lexer/lexers/section/section.test.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
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
TEST(SectionLexer, Constructor)
{
    mark_sideways::State state;
    mark_sideways::lexers::Section section(&state);
}

// Test the lexer's method lex().
// Ensures that the lexer correctly lexes a simple section headline.
TEST(SectionLexer, SimpleHeadline)
{
    mark_sideways::State state;
    mark_sideways::lexers::Section section(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=1,TITLE=Section."));
    std::vector<mark_sideways::Token> actual = section.lex("# Section.");
    EXPECT_TRUE(tokens_equal(expected, actual));

    actual = section.lex("# Section.\n");
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the Section lexer's method lex().
// Ensures that the lexer correctly lexes a header with internal symbols.
TEST(SectionLexer, SpecialSymbols)
{
    mark_sideways::State state;
    mark_sideways::lexers::Section section(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=1,TITLE=Section with whitespace."));
    std::vector<mark_sideways::Token> actual = section.lex("# Section with whitespace.");
    EXPECT_TRUE(tokens_equal(expected, actual));

    actual = section.lex("# Section with whitespace.\n");
    EXPECT_TRUE(tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=1,TITLE=Section with *asterisks.*"));
    actual = section.lex("# Section with *asterisks.*");
    EXPECT_TRUE(tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=1,TITLE=Section with an arrow. ->"));
    actual = section.lex("# Section with an arrow. ->");
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the Section lexer's method lex().
// Ensures that the lexer correctly lexes various levels of headlines.
TEST(SectionLexer, HeadlineLevels)
{
    mark_sideways::State state;
    mark_sideways::lexers::Section section(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=1,TITLE=Section."));
    std::vector<mark_sideways::Token> actual = section.lex("# Section.");
    EXPECT_TRUE(tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=2,TITLE=Subsection."));
    actual = section.lex("## Subsection.");
    EXPECT_TRUE(tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=3,TITLE=Subsubsection."));
    actual = section.lex("### Subsubsection.");
    EXPECT_TRUE(tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=4,TITLE=Subsubsubsection."));
    actual = section.lex("#### Subsubsubsection.");
    EXPECT_TRUE(tokens_equal(expected, actual));

    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=5,TITLE=Subsubsubsubsection."));
    actual = section.lex("##### Subsubsubsubsection.");
    EXPECT_TRUE(tokens_equal(expected, actual));
}

// Test the Section lexer's method lex().
// Ensures that the lexer correctly leaves the input string unmodified when given a string with no section headline.
TEST(SectionLexer, NoHeadline)
{
    mark_sideways::State state;
    mark_sideways::lexers::Section section(&state);

    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, "This is a paragraph."));
    std::vector<mark_sideways::Token> actual = section.lex("This is a paragraph.");
    EXPECT_TRUE(tokens_equal(expected, actual));
}
