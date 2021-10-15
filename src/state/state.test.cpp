// src/state/state.test.cpp
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
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

// Test the State class's constructor.
// Ensures that no exceptions are thrown.
TEST(State, Constructor)
{
    mark_sideways::State state;
}

// Test the State class's method indent().
TEST(State, Indent)
{
    mark_sideways::State state;

    std::string expected = "";
    std::string actual = state.indent();
    EXPECT_EQ(expected, actual);

    state.begin_list(1, mark_sideways::State::level_type::itemize);
    expected = "    ";
    actual = state.indent();
    EXPECT_EQ(expected, actual);

    state.begin_list(2, mark_sideways::State::level_type::enumerate);
    expected = "        ";
    actual = state.indent();
    EXPECT_EQ(expected, actual);

    state.begin_list(1, mark_sideways::State::level_type::itemize);
    expected = "    ";
    actual = state.indent();
    EXPECT_EQ(expected, actual);
}

// Test the State class's methods is_verbatim() and toggle_verbatim().
TEST(State, Verbatim)
{
    mark_sideways::State state;
    EXPECT_FALSE(state.is_verbatim());

    state.toggle_verbatim();
    EXPECT_TRUE(state.is_verbatim());

    state.toggle_verbatim();
    EXPECT_FALSE(state.is_verbatim());
}

// Test the State class's methods is_math() and toggle_math().
TEST(State, Math)
{
    mark_sideways::State state;
    EXPECT_FALSE(state.is_math());

    state.toggle_math();
    EXPECT_TRUE(state.is_math());

    state.toggle_math();
    EXPECT_FALSE(state.is_math());
}

// Test the State class's methods is_head() and end_head().
TEST(State, Head)
{
    mark_sideways::State state;
    EXPECT_TRUE(state.is_head());

    state.end_head();
    EXPECT_FALSE(state.is_head());
}

// Test the State class's methods decrease_list_level(), get_list_level(), and get_list_type().
TEST(State, DecreaseListLevel)
{
    mark_sideways::State state;
    EXPECT_EQ(0, state.get_list_level());
    EXPECT_THROW(state.get_list_type(), std::runtime_error);

    state.decrease_list_level(0);
    EXPECT_EQ(0, state.get_list_level());

    state.begin_list(1, mark_sideways::State::level_type::itemize);
    EXPECT_EQ(1, state.get_list_level());
    EXPECT_EQ(mark_sideways::State::level_type::itemize, state.get_list_type());

    state.decrease_list_level(1);
    EXPECT_EQ(1, state.get_list_level());

    state.decrease_list_level(0);
    EXPECT_EQ(0, state.get_list_level());

    state.decrease_list_level(1);
    EXPECT_EQ(0, state.get_list_level());

    state.begin_list(1, mark_sideways::State::level_type::itemize);
    EXPECT_EQ(mark_sideways::State::level_type::itemize, state.get_list_type());
    EXPECT_EQ(1, state.get_list_level());

    state.begin_list(2, mark_sideways::State::level_type::enumerate);
    EXPECT_EQ(mark_sideways::State::level_type::enumerate, state.get_list_type());
    EXPECT_EQ(2, state.get_list_level());

    state.decrease_list_level(2);
    EXPECT_EQ(2, state.get_list_level());

    state.decrease_list_level(0);
    EXPECT_EQ(0, state.get_list_level());
}

// Test the State class's method begin_list().
TEST(State, BeginList)
{
    mark_sideways::State state;

    state.begin_list(1, mark_sideways::State::level_type::itemize);
    EXPECT_EQ(1, state.get_list_level());
    EXPECT_EQ(mark_sideways::State::level_type::itemize, state.get_list_type());

    state.begin_list(2, mark_sideways::State::level_type::enumerate);
    EXPECT_EQ(2, state.get_list_level());
    EXPECT_EQ(mark_sideways::State::level_type::enumerate, state.get_list_type());

    state.begin_list(1, mark_sideways::State::level_type::itemize);
    EXPECT_EQ(1, state.get_list_level());
    EXPECT_EQ(mark_sideways::State::level_type::itemize, state.get_list_type());

    state.begin_list(2, mark_sideways::State::level_type::enumerate);
    EXPECT_EQ(2, state.get_list_level());
    EXPECT_EQ(mark_sideways::State::level_type::enumerate, state.get_list_type());

    state.begin_list(3, mark_sideways::State::level_type::itemize);
    EXPECT_EQ(3, state.get_list_level());
    EXPECT_EQ(mark_sideways::State::level_type::itemize, state.get_list_type());

    state.begin_list(5, mark_sideways::State::level_type::itemize);
    EXPECT_EQ(5, state.get_list_level());
    EXPECT_EQ(mark_sideways::State::level_type::itemize, state.get_list_type());
}
