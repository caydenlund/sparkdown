// src/state/state.test.cpp
// v. 0.1.1
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the State class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <gtest/gtest.h>
#include <string>

#include "state.hpp"

using namespace mark_sideways;

// Tests the State class's constructor.
// Ensures that the State constructor doesn't throw an exception.
TEST(State, Constructor)
{
    State state = State();
}

// Tests the State class's method indent().
// Ensures that the State class's method indent() returns the correct value
// for various indentation levels.
TEST(State, IndentCorrectness)
{
    State state = State();

    std::string expected = "";
    std::string actual = state.indent();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
    
    state.begin_itemize(1);
    expected = "    ";
    actual = state.indent();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state.begin_itemize(2);
    expected = "        ";
    actual = state.indent();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state.begin_enumerate(2);
    expected = "        ";
    actual = state.indent();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state.set_indentation(1);
    expected = "    ";
    actual = state.indent();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state.begin_enumerate(2);
    expected = "        ";
    actual = state.indent();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state.set_indentation(0);
    expected = "";
    actual = state.indent();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// Tests the State class's method begin_itemize().
// Ensures that the State class's method begin_itemize() returns the correct
// value for various itemize levels.
TEST(State, BeginItemize)
{
    State state = State();
    state.begin_itemize(1);
    std::string expected = "\\begin{itemize}\n    ";
    std::string actual = state.get_product();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state = State();
    state.begin_itemize(2);
    expected = "\\begin{itemize}\n    \\begin{itemize}\n        ";
    actual = state.get_product();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
    state.begin_itemize(1);
    expected = "    \\end{itemize}\n    ";
    actual = state.get_product();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// Tests the State class's method begin_enumerate().
// Ensures that the State class's method begin_enumerate() returns the correct
// value for various enumerate levels.
TEST(State, BeginEnumerate)
{
    State state = State();
    state.begin_enumerate(1);
    std::string expected = "\\begin{enumerate}\n    ";
    std::string actual = state.get_product();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state = State();
    state.begin_enumerate(2);
    expected = "\\begin{enumerate}\n    \\begin{enumerate}\n        ";
    actual = state.get_product();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
    state.begin_enumerate(1);
    expected = "    \\end{enumerate}\n    ";
    actual = state.get_product();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// Test the State class's methods get_line() and set_line().
TEST(State, GetSetLine)
{
    State state = State();
    state.set_line("test");
    std::string expected = "test";
    std::string actual = state.get_line();
    EXPECT_STREQ(expected.c_str(), actual.c_str());

    state = State();
    state.set_line("test");
    state.set_line("test2");
    expected = "test2";
    actual = state.get_line();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// Test the State class's methods is_verbatim() and toggle_verbatim().
TEST(State, Verbatim)
{
    State state = State();
    EXPECT_FALSE(state.is_verbatim());
    std::string expected = "\\begin{verbatim}";
    std::string actual = state.toggle_verbatim();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
    EXPECT_TRUE(state.is_verbatim());
}

// Test that the State class's method get_product() does not indent
// inside of verbatim blocks.
TEST(State, VerbatimIndent)
{
    State state = State();
    state.begin_itemize(1);
    state.toggle_verbatim();
    state.set_line("test");
    std::string expected = "\\begin{itemize}\ntest";
    std::string actual = state.get_product();
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}
