// //parser/tests:parser.tests.math.block
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with block math expressions.
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
// Ensure that the parser can correctly parse a single simple block math expression.
TEST(ParserMathBlock, Simple)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "\\[1 + 2 + 3\\]";
    std::string expected = "\\[1 + 2 + 3\\]\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores special symbols in block math expressions.
TEST(ParserMathBlock, SymbolsInside)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "\\[1*2*3\\]";
    std::string expected = "\\[1*2*3\\]\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly parses special symbols between block math expressions.
TEST(ParserMathBlock, SymbolsBetween)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "\\[1*2*3\\] *4* \\[5*6*7\\]";
    std::string expected = "\\[1*2*3\\] \\textit{4} \\[5*6*7\\]\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores escaped dollar signs in block math expressions.
TEST(ParserMathBlock, EscapedDollar)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "\\[\\$1*2*3\\]";
    std::string expected = "\\[\\$1*2*3\\]\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores special symbols in block math expressions.
// This test specifically tests items on new lines.
TEST(ParserMathBlock, EscapedSymbols)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::stringstream input;
    input << "\\[" << std::endl
          << "  1" << std::endl
          << "  * ->" << std::endl
          << "\\]" << std::endl;

    std::stringstream expected;
    expected << "\\[" << std::endl
             << "  1" << std::endl
             << "  * \\rightarrow" << std::endl
             << "\\]" << std::endl;

    std::string output = parser.parse(input.str());

    EXPECT_EQ(expected.str(), output);
}
