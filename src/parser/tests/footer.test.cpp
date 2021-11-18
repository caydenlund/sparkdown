// //parser:parser.footer.test
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 11/18/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#end() function.
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

// Test the Parser#end() function.
// Ensure that the parser can correctly return the footer of a simple (empty) file.
TEST(ParserFooter, EndEmpty)
{
    sparkdown::Parser parser;
    parser.parse("");

    std::string expected = "\n\\end{document}\n";

    EXPECT_EQ(expected, parser.end());
}

// Test the Parser#end() function.
// Ensure that the parser can correctly return the footer of a file with an unterminated bulleted list.
TEST(ParserFooter, EndBulletedList)
{
    sparkdown::Parser parser;
    parser.parse("* Bullet point.");

    std::stringstream expected;
    expected << "\\end{itemize}" << std::endl
             << std::endl
             << "\\end{document}" << std::endl;

    EXPECT_EQ(expected, parser.end());
}

// Test the Parser#end() function.
// Ensure that the parser can correctly return the hfooter of a file with nested unterminated lists.
TEST(ParserFooter, EndNestedLists)
{
    sparkdown::Parser parser;
    parser.parse("* Bullet point.");
    parser.parse("  1. Numbered list item.");

    std::stringstream expected;
    expected << "    \\end{enumerate}" << std::endl
             << "\\end{itemize}" << std::endl
             << std::endl
             << "\\end{document}" << std::endl;

    EXPECT_EQ(expected, parser.end());
}
