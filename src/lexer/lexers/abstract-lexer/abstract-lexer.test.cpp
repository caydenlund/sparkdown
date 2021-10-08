// src/lexer/lexers/abstract-lexer/abstract-lexer.test.cpp
// v. 0.4.2
//
// Author: Cayden Lund
//   Date: 10/07/2021
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
    // * std::string line   - The line to lex.
    // * return std::vector<mark_sideways::Token> - The tokens found in the line.
    std::vector<mark_sideways::Token> lex(std::string line)
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

    // A static function to test the equality of two token vectors.
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
    EXPECT_TRUE(ConcreteLexer::tokens_equal(expected, actual));

    state.toggle_verbatim();
    expected.clear();
    expected.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, input));
    actual = lexer.lex(input);
    EXPECT_TRUE(ConcreteLexer::tokens_equal(expected, actual));
}
