// //parser:parser.verb.inline.test
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with inline verbatim expressions.
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
// Ensure that the parser can correctly parse a single simple inline verbatim expression.
TEST(ParserVerbInline, Simple)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "|1 + 2 + 3|";
    std::string expected = "\\verb|1 + 2 + 3|\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores special symbols in inline verbatim expressions.
TEST(ParserVerbInline, SymbolsInside)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "|1*2*3|";
    std::string expected = "\\verb|1*2*3|\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly parses special symbols between inline verbatim expressions.
TEST(ParserVerbInline, SymbolsBetween)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "|1*2*3| *4* |5*6*7|";
    std::string expected = "\\verb|1*2*3| \\textit{4} \\verb|5*6*7|\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse() function.
// Ensure that the parser correctly ignores escaped pipes outside of inline verbatim expressions.
TEST(ParserVerbInline, EscapedPipeOutside)
{
    // Create a Parser object.
    sparkdown::Parser parser;
    parser.parse("");

    std::string input = "\\|*1*|2*3*4|";
    std::string expected = "|\\textit{1}\\verb|2*3*4|\n";
    std::string output = parser.parse(input);

    EXPECT_EQ(expected, output);
}
