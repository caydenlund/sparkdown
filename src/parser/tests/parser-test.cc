// src/lib/parser/tests/parser-test.cc
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 09/23/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the unit tests for the Parser class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <gtest/gtest.h>
#include <string>

#include "lib/parser/parser.h"

// Test the Parser::Parser() zero-argument constructor.
// This test is expected to pass unless the constructor throws an exception.
TEST(ParserTest, Constructor) {
    Parser parser = Parser();
}

// Test the Parser#parse_line() method.
// This test is expected to pass unless the method throws an exception.
TEST(ParserTest, ParseLine) {
    Parser parser = Parser();
    parser.parse_line("This is unformatted text.");
}

// Test the Parser#parse_line() method.
// This test ensures that unformatted text is correctly returned unmodified.
TEST(ParserTest, UnformattedText)
{
    Parser parser = Parser();
    std::string input = "This is unformatted text.";
    std::string output = parser.parse_line(input);
    EXPECT_EQ(input, output);
}

// Test the Parser#parse_line() method.
// This test ensures that a section header is correctly returned in LaTeX format.
TEST(ParserTest, SectionHeader)
{
    Parser parser = Parser();
    std::string input = "# This is a section header.";
    std::string output = parser.parse_line(input);
    std::string expected = "\\section*{This is a section header.}";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that a single bullet point is correctly returned in LaTeX format.
TEST(ParserTest, SingleBulletPoint)
{
    Parser parser = Parser();

    std::string input = "* This is a bullet point.";

    std::string output = parser.parse_line(input);

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point.";

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that a set of two equally-nested bullet points
// is correctly returned in LaTeX format.
TEST(ParserTest, MultipleEqualBulletPoints)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "* This is a bullet point." << std::endl;
    input << "* This is a second bullet point.";

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;
    expected << "    \\item This is a second bullet point.";

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that a sub-bullet point is correctly returned in LaTeX format.
TEST(ParserTest, SubBulletPoint)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "* This is a bullet point." << std::endl;
    input << "  * This is a sub-bullet point.";

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;
    expected << "    \\begin{itemize}" << std::endl;
    expected << "        \\item This is a sub-bullet point.";

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that the parser can enter a sub-bullet point list
// and then exit from it.
TEST(ParserTest, SubBulletPointExit)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "* This is a bullet point." << std::endl;
    input << "  * This is a sub-bullet point." << std::endl;
    input << "* This is another top-level bullet point.";

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;
    expected << "    \\begin{itemize}" << std::endl;
    expected << "        \\item This is a sub-bullet point." << std::endl;
    expected << "    \\end{itemize}" << std::endl;
    expected << "    \\item This is another top-level bullet point.";

    EXPECT_EQ(expected.str(), output);
}