// //parser:parser.enumerate.test
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with ordered lists.
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

// Test the Parser#parse() method.
// Ensure that the parser can correctly parse a single list item.
TEST(ParserEnumerate, Single)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::string input = "1. List item.";

      std::stringstream expected;
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item." << std::endl;

      std::string actual = parser.parse(input);

      EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly parse two equally-nested list items.
TEST(ParserEnumerate, Double)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "1. List item 1." << std::endl
            << "2. List item 2." << std::endl;

      std::stringstream expected;
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item 1." << std::endl
               << "    \\item List item 2." << std::endl;

      std::string actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly parse nested list items.
TEST(ParserEnumerate, Nested)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "1. List item 1." << std::endl
            << "2. List item 2." << std::endl
            << "    1. List item 2.1." << std::endl
            << "    2. List item 2.2." << std::endl;

      std::stringstream expected;
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item 1." << std::endl
               << "    \\item List item 2." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item 2.1." << std::endl
               << "            \\item List item 2.2." << std::endl;

      std::string actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with a different indentation and numbering system.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "1. List item 1." << std::endl
            << "2. List item 2." << std::endl
            << "  a. List item 2.a." << std::endl
            << "  b. List item 2.b." << std::endl;

      expected.str("");
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item 1." << std::endl
               << "    \\item List item 2." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item 2.a." << std::endl
               << "            \\item List item 2.b." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly resume the proper nesting levels.
TEST(ParserEnumerate, ResumeLevel)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "1. List item 1." << std::endl
            << "2. List item 2." << std::endl
            << "  1. List item 2.1." << std::endl
            << "  1. List item 2.2." << std::endl
            << "3. List item 3." << std::endl;

      std::stringstream expected;
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item 1." << std::endl
               << "    \\item List item 2." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item 2.1." << std::endl
               << "            \\item List item 2.2." << std::endl
               << "        \\end{enumerate}" << std::endl
               << "    \\item List item 3." << std::endl;
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly match content with its parent list item.
TEST(ParserEnumerate, ChildContent)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "1. List item 1." << std::endl
            << "  Some content for list item 1." << std::endl
            << "  a. List item a." << std::endl
            << "    Some content for list item a." << std::endl
            << "  More content for list item 1." << std::endl
            << "Some top-level content." << std::endl;

      std::stringstream expected;
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item 1." << std::endl
               << "        Some content for list item 1." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item a." << std::endl
               << "            Some content for list item a." << std::endl
               << "        \\end{enumerate}" << std::endl
               << "        More content for list item 1." << std::endl
               << "\\end{enumerate}" << std::endl
               << "Some top-level content." << std::endl;

      std::string actual = parser.parse("input");

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with a different indentation.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "1. List item 1." << std::endl
            << "  Some content for list item 1." << std::endl
            << "    2. List item 2." << std::endl
            << "      Some content for list item 2." << std::endl
            << "  More content for list item 1." << std::endl
            << "Some top-level content." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with yet another form of indentation.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "1. List item 1." << std::endl
            << "    Some content for list item 1." << std::endl
            << "    a. List item 2." << std::endl
            << "        Some content for list item 2." << std::endl
            << "    More content for list item 1." << std::endl
            << "Some top-level content." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly detect the list level based on its numbering system.
TEST(ParserEnumerate, DetectLevel)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "1. List item 1." << std::endl
            << "  1. List item 1.1." << std::endl
            << "    1. List item 1.1.1." << std::endl
            << "  2. List item 1.2." << std::endl
            << "2. List item 2." << std::endl
            << "  1. List item 2.1." << std::endl
            << "    1. List item 2.1.1." << std::endl
            << "  2. List item 2.2." << std::endl
            << "3. List item 3." << std::endl;

      std::stringstream expected;
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item 1." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item 1.1." << std::endl
               << "                \\begin{enumerate}" << std::endl
               << "                    \\item List item 1.1.1." << std::endl
               << "                \\end{enumerate}" << std::endl
               << "            \\item List item 1.2." << std::endl
               << "        \\end{enumerate}" << std::endl
               << "    \\item List item 2." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item 2.1." << std::endl
               << "                \\begin{enumerate}" << std::endl
               << "                    \\item List item 2.1.1." << std::endl
               << "                \\end{enumerate}" << std::endl
               << "            \\item List item 2.2." << std::endl
               << "        \\end{enumerate}" << std::endl
               << "    \\item List item 3." << std::endl;

      std::string actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with messed up indentation.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "1. List item 1." << std::endl
            << "  1. List item 1.1." << std::endl
            << "      1. List item 1.1.1." << std::endl
            << "    2. List item 1.2." << std::endl
            << "2. List item 2." << std::endl
            << "    1. List item 2.1." << std::endl
            << "      1. List item 2.1.1." << std::endl
            << "  2. List item 2.2." << std::endl
            << "3. List item 3." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with a different numbering system.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "1. List item 1." << std::endl
            << "  a. List item 1.a." << std::endl
            << "    i. List item 1.a.i." << std::endl
            << "    ii. List item 1.a.ii." << std::endl
            << "  b. List item 1.b." << std::endl
            << "2. List item 2." << std::endl
            << "  a. List item 2.a." << std::endl
            << "    i. List item 2.a.i." << std::endl
            << "    ii. List item 2.a.ii." << std::endl
            << "  b. List item 2.b." << std::endl
            << "3. List item 3." << std::endl;

      expected.str("");
      expected << "\\begin{enumerate}" << std::endl
               << "    \\item List item 1." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item 1.a." << std::endl
               << "                \\begin{enumerate}" << std::endl
               << "                    \\item List item 1.a.i." << std::endl
               << "                    \\item List item 1.a.ii." << std::endl
               << "                \\end{enumerate}" << std::endl
               << "            \\item List item 1.b." << std::endl
               << "        \\end{enumerate}" << std::endl
               << "    \\item List item 2." << std::endl
               << "        \\begin{enumerate}" << std::endl
               << "            \\item List item 2.a." << std::endl
               << "                \\begin{enumerate}" << std::endl
               << "                    \\item List item 2.a.i." << std::endl
               << "                    \\item List item 2.a.ii." << std::endl
               << "                \\end{enumerate}" << std::endl
               << "            \\item List item 2.b." << std::endl
               << "        \\end{enumerate}" << std::endl
               << "    \\item List item 3." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with messed up indentation.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "1. List item 1." << std::endl
            << "  a. List item 1.a." << std::endl
            << "    i. List item 1.a.i." << std::endl
            << "ii. List item 1.a.ii" << std::endl
            << "    b. List item 1.b." << std::endl
            << "2. List item 2." << std::endl
            << "  a. List item 2.a." << std::endl
            << "    i. List item 2.a.i." << std::endl
            << "  ii. List item 2.a.ii." << std::endl
            << "  b. List item 2.b." << std::endl
            << "3. List item 3." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);
}
