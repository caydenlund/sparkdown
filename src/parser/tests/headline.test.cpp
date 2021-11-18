// //parser:parser.headline.test
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 11/18/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with section headlines.
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
// Ensure that the parser can correctly parse a single simple section headline.
TEST(ParserHeadline, Simple)
{
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "# Headline.";

    std::string expected = "\\section*{Headline.}\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that the parser can correctly parse a single sub-sub-headline.
TEST(ParserHeadline, SubSubHeadline)
{
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "### Sub-sub-headline.";

    std::string expected = "\\subsubsection*{Sub-sub-headline.}\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}
