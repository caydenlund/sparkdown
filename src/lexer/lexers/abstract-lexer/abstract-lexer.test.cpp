// src/lexer/lexers/abstract-lexer/abstract-lexer.test.cpp
// v. 0.4.4
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the AbstractLexer class.
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

// The AbstractLexer class.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

// Since the AbstractLexer class is abstract, we need to create a concrete
// class to test it.
class ConcreteLexer : public mark_sideways::lexers::AbstractLexer
{
public:
    // The constructor.
    ConcreteLexer(mark_sideways::State *state) : mark_sideways::lexers::AbstractLexer(state) {}

    // The destructor.
    virtual ~ConcreteLexer() {}

    // The lex function.
    //
    // * const std::string &line   - The line to lex.
    // * return std::vector<mark_sideways::Token> - The tokens found in the line.
    std::vector<mark_sideways::Token> lex(const std::string &line)
    {
        std::vector<mark_sideways::Token> tokens;
        if (state->is_verbatim())
        {
            tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, line));
        }
        else
        {
            tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, line));
        }
        return tokens;
    }
};

// Ensure that the constructor throws no exceptions.
TEST(AbstractLexer, ConstructorNoFail)
{
    // Create a new state.
    mark_sideways::State state;

    // Create a new lexer.
    ConcreteLexer lexer(&state);

    state.toggle_verbatim();
}

// Ensure that the lex function can correctly access the state object.
TEST(AbstractLexer, AccessState)
{
    // Create a new state.
    mark_sideways::State state;

    // Create a new lexer.
    ConcreteLexer lexer(&state);

    std::string input = "Line";
    std::vector<mark_sideways::Token> expected;
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, input));
    std::vector<mark_sideways::Token> actual = lexer.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));

    state.toggle_verbatim();
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, input));
    actual = lexer.lex(input);
    EXPECT_TRUE(mark_sideways::Token::tokens_equal(expected, actual));
}
