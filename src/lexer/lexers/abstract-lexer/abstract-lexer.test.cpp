// src/lexer/lexers/abstract-lexer/abstract-lexer.test.cpp
// v. 0.2.0
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

// The GTest testing framework.
#include <gtest/gtest.h>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

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
    // * return std::string - The lexed line.
    std::string lex(std::string line)
    {
        if (state->is_verbatim())
            return line;
        std::smatch match;
        if (std::regex_search(line, match, this->unlexed_regex))
        {
            return match.str(1);
        }
        return "Test";
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
    std::string expected = "Test";
    std::string actual = lexer.lex(input);
    ASSERT_EQ(expected, actual);

    state.toggle_verbatim();
    expected = input;
    actual = lexer.lex(input);
    ASSERT_EQ(expected, actual);
}

// Ensure that the lex function can correctly match the unlexed_token regular expression.
TEST(AbstractLexer, LexUnlexedToken)
{
    // Create a new state.
    mark_sideways::State state;

    // Create a new lexer.
    ConcreteLexer lexer(&state);

    std::string input = "[%%UNLEXED=123%%]";
    std::string expected = "123";
    std::string actual = lexer.lex(input);
    ASSERT_EQ(expected, actual);

    input = "123 [%%UNLEXED=456%%] 789";
    expected = "456";
    actual = lexer.lex(input);
    ASSERT_EQ(expected, actual);
}
