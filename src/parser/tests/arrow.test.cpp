// //parser:parser.arrow.test
// v. 0.1.2
//
// Author: Cayden Lund
//   Date: 11/03/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with arrows.
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
// Ensure that the parser can correctly parse a single simple arrow.
TEST(ParserArrow, Simple)
{
    sparkdown::Parser parser;
    // Pass an empty string so that we don't include the header in the output.
    parser.parse("");

    std::string input = "->";

    std::string expected = "$\\rightarrow$\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that the parser can correctly parse multiple types of arrows.
TEST(ParserArrow, Multiple)
{
    sparkdown::Parser parser;
    // Pass an empty string so that we don't include the header in the output.
    parser.parse("");

    std::string input = "=> <-- <==>";

    std::string expected = "$\\Rightarrow$ $\\longleftarrow$ $Longleftrightarrow$\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that the parser can correctly parse arrows inside and outside of the inline math context.
TEST(ParserArrow, MathInline)
{
    sparkdown::Parser parser;
    // Pass an empty string so that we don't include the header in the output.
    parser.parse("");

    std::string input = "-> $->$ $3 -> 5$";

    std::string expected = "$\\rightarrow$ $\\rightarrow$ $3 \\rightarrow 5$\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that the parser can correctly parse arrows inside of the math block context.
TEST(ParserArrow, MathBlock)
{
    sparkdown::Parser parser;
    parser.parse("\\[");

    std::string input = "->";

    std::string expected = "\\rightarrow\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores arrows inside of the inline verbatim context.
TEST(ParserArrow, VerbInline)
{
    sparkdown::Parser parser;
    // Pass an empty string so that we don't include the header in the output.
    parser.parse("");

    std::string input = "|->|";

    std::string expected = "\\verb|->|\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores arrows inside of the verbatim block context.
TEST(ParserArrow, VerbBlock)
{
    sparkdown::Parser parser;
    parser.parse("```");

    std::string input = "->";

    std::string expected = "->\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores arrows that are escaped.
TEST(ParserArrow, Escaped)
{
    sparkdown::Parser parser;
    // Pass an empty string so that we don't include the header in the output.
    parser.parse("");

    std::string input = "\\-> $\\->$ |\\->|";

    std::string expected = "-> $->$ \\verb|\\->|\n";

    std::string actual = parser.parse(input);

    EXPECT_EQ(expected, actual);
}
