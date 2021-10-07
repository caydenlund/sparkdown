// src/lexer/lexers/abstractLexer/abstractLexer.test.cpp
// v. 0.1.0
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

// The GTest testing framework.
#include <gtest/gtest.h>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

// The AbstractLexer class.
#include "lexer/lexers/abstractLexer/abstractLexer.hpp"

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