// //parser:parser.misc.test
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 11/18/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with a few miscellaneous items.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <sstream>

// The GTest testing framework.
#include <gtest/gtest.h>

// The Parser header file.
#include "parser/parser.hpp"

// Test the Parser#parse() function.
// Ensure that the parser can correctly parse multiple lines.
TEST(Parser, MultipleLines)
{
    sparkdown::Parser parser;
    parser.parse("");

    std::stringstream input;
    input << "* Bullet 1." << std::endl
          << "* Bullet 2." << std::endl;

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl
             << "    \\item Bullet 1." << std ::endl
             << "    \\item Bullet 2." << std::endl;

    std::string actual = parser.parse(input.str());

    EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() function.
// Ensure that the output is identical regardless of whether there are terminating newlines in the input.
TEST(Parser, TerminatingNewLines)
{
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "Line.";
    std::string expected = "Line.";
    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);

    input += "\n";
    actual = parser.parse(input);

    EXPECT_EQ(expected, actual);

    input += "\n";
    expected += "\n";
    actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that output is identical between the parse() and string operator variants.
