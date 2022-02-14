// //parser/tests:parser.tests.math.inline
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with inline math expressions.
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
// Ensure that the parser can correctly parse a single simple inline math expression.
TEST(ParserMathInline, Simple)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "$1 + 2 + 3$";
    std::string expected = "$1 + 2 + 3$\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores special symbols in inline math expressions.
TEST(ParserMathInline, SymbolsInside)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "$1*2*3$";
    std::string expected = "$1*2*3$\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly parses special symbols between inline math expressions.
TEST(ParserMathInline, SymbolsBetween)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "$1*2*3$ *4* $5*6*7$";
    std::string expected = "$1*2*3$ \\textit{4} $5*6*7$\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores escaped dollar signs in inline math expressions.
TEST(ParserMathInline, EscapedDollar)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "$\\$1*2*3$";
    std::string expected = "$\\$1*2*3$\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores escaped dollar signs outside of inline math expressions.
TEST(ParserMathInline, EscapedDollarOutside)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "\\$*1*$2*3*4$";
    std::string expected = "\\$\\textit{1}$2*3*4$\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}
