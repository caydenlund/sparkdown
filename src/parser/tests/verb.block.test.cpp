// //parser:parser.verbatim.block.test
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with block verbatim expressions.
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
// Ensure that the parser can correctly parse a single simple block verbatim expression.
TEST(ParserVerbBlock, Simple)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "```1 + 2 + 3```";
    std::string expected = "\\begin{verbatim}1 + 2 + 3\\end{verbatim}\n";
    std::string output = parser.parse(input);

    // EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores special symbols in block verbatim expressions.
TEST(ParserVerbBlock, SymbolsInside)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "```1*2*3```";
    std::string expected = "\\begin{verbatim}1*2*3\\end{verbatim}\n";
    std::string output = parser.parse(input);

    // EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly parses special symbols between block verbatim expressions.
TEST(ParserVerbBlock, SymbolsBetween)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "```1*2*3$ *4* $5*6*7```";
    std::string expected = "\\begin{verbatim}1*2*3\\end{verbatim} \\textit{4} \\begin{verbatim}5*6*7\\end{verbatim}\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores escaped dollar signs in block verbatim expressions.
TEST(ParserVerbBlock, EscapedDollar)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "```\\$1*2*3```";
    std::string expected = "\\begin{verbatim}\\$1*2*3\\end{verbatim}\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores special symbols in block verbatim expressions.
// This test specifically tests items on new lines.
TEST(ParserVerbBlock, EscapedSymbols)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::stringstream input;
    input << "```" << std::endl
          << "  1" << std::endl
          << "  * \\->" << std::endl
          << "\\end{verbatim}" << std::endl;

    std::stringstream expected;
    expected << "\\begin{verbatim}" << std::endl
             << "  1" << std::endl
             << "  * \\->" << std::endl
             << "\\end{verbatim}" << std::endl;

    std::string output = parser.parse(input.str());

    EXPECT_EQ(expected.str(), output);
}
