// //parser:parser.itemize.test
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 11/03/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with unordered lists.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <sstream>

// The GTest testing framework.
#include <gtest/gtest.h>

// The Parser header file.
#include "parser.hpp"

// Test the Parser#parse() method.
// Ensure that the parser can correctly parse a single bullet point.
TEST(ParserItemize, Single)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::string input = "* Bullet.";

      std::stringstream expected;
      expected << "\\begin{itemize}" << std::endl
               << "    \\item Bullet." << std::endl;

      std::string actual = parser.parse(input);

      EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly parse two equally-nested bullet points.
TEST(ParserItemize, Double)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "* Bullet 1." << std::endl
            << "* Bullet 2." << std::endl;

      std::stringstream expected;
      expected << "\\begin{itemize}" << std::endl
               << "    \\item Bullet." << std::endl;

      std::string actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly parse nested bullet points.
TEST(ParserItemize, Nested)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "* Bullet 1." << std::endl
            << "* Bullet 2." << std::endl
            << "    * Bullet 2.1." << std::endl
            << "    * Bullet 2.2." << std::endl;

      std::stringstream expected;
      expected << "\\begin{itemize}" << std::endl
               << "    \\item Bullet 1." << std::endl
               << "    \\item Bullet 2." << std::endl
               << "        \\begin{itemize}" << std::endl
               << "            \\item Bullet 2.1." << std::endl
               << "            \\item Bullet 2.2." << std::endl;

      std::string actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with a different indentation.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "* Bullet 1." << std::endl
            << "* Bullet 2." << std::endl
            << "  * Bullet 2.1." << std::endl
            << "  * Bullet 2.2." << std::endl;

      expected.str("");
      expected << "\\begin{itemize}" << std::endl
               << "    \\item Bullet 1." << std::endl
               << "    \\item Bullet 2." << std::endl
               << "        \\begin{itemize}" << std::endl
               << "            \\item Bullet 2.1." << std::endl
               << "            \\item Bullet 2.2." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly resume the proper nesting levels.
TEST(ParserItemize, ResumeLevel)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "* Bullet 1." << std::endl
            << "* Bullet 2." << std::endl
            << "  * Bullet 2.1." << std::endl
            << "  * Bullet 2.2." << std::endl
            << "* Bullet 3." << std::endl;

      std::stringstream expected;
      expected << "\\begin{itemize}" << std::endl
               << "    \\item Bullet 1." << std::endl
               << "    \\item Bullet 2." << std::endl
               << "        \\begin{itemize}" << std::endl
               << "            \\item Bullet 2.1." << std::endl
               << "            \\item Bullet 2.2." << std::endl
               << "        \\end{itemize}" << std::endl
               << "    \\item Bullet 3." << std::endl;
}

// Test the Parser#parse() method.
// Ensure that the parser can correctly match content with its parent bullet point.
TEST(ParserItemize, ChildContent)
{
      sparkdown::Parser parser;
      parser.parse("");

      std::stringstream input;
      input << "* Bullet 1." << std::endl
            << "  Some content for bullet 1." << std::endl
            << "  * Bullet 2." << std::endl
            << "    Some content for bullet 2." << std::endl
            << "  More content for bullet 1." << std::endl
            << "Some top-level content." << std::endl;

      std::stringstream expected;
      expected << "\\begin{itemize}" << std::endl
               << "    \\item Bullet 1." << std::endl
               << "        Some content for bullet 1." << std::endl
               << "        \\begin{itemize}" << std::endl
               << "            \\item Bullet 2." << std::endl
               << "            Some content for bullet 2." << std::endl
               << "        \\end{itemize}" << std::endl
               << "        More content for bullet 1." << std::endl
               << "\\end{itemize}" << std::endl
               << "Some top-level content." << std::endl;

      std::string actual = parser.parse("input");

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with a different indentation.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "* Bullet 1." << std::endl
            << "  Some content for bullet 1." << std::endl
            << "    * Bullet 2." << std::endl
            << "      Some content for bullet 2." << std::endl
            << "  More content for bullet 1." << std::endl
            << "Some top-level content." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);

      // Same thing, but with yet another form of indentation.
      parser = sparkdown::Parser();
      parser.parse("");

      input.str("");
      input << "* Bullet 1." << std::endl
            << "    Some content for bullet 1." << std::endl
            << "    * Bullet 2." << std::endl
            << "        Some content for bullet 2." << std::endl
            << "    More content for bullet 1." << std::endl
            << "Some top-level content." << std::endl;

      actual = parser.parse(input.str());

      EXPECT_EQ(expected.str(), actual);
}
