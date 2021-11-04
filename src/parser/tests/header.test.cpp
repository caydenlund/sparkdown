// //parser:parser.header.test
// v. 0.1.2
//
// Author: Cayden Lund
//   Date: 11/03/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a subset of the unit tests for the Parser class.
// These tests specifically test the Parser#parse() function with document headers.
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

// A helper method that builds the expected document head from the given inputs.
//
// * const  std::string &title  - The title of the document. Defaults to "Notes".
// * const  std::string &author - The author of the document. Defaults to "Cayden Lund".
// * const  std::string &date   - The date of the document. Defaults to "".
// * const  std::string &extra  - The non-standard extra header lines in the document. Defaults to "".
// * return std::string         - The expected document head.
std::string build_document_head(const std::string &title = "Notes",
                                const std::string &author = "Cayden Lund",
                                const std::string &date = "",
                                const std::string &extra = "")
{
    std::stringstream head;
    head << "\\title{" << title << "}" << std::endl
         << "\\author{" << author << "}" << std::endl
         << "\\date{" << date << "}" << std::endl
         << std::endl
         << "\\documentclass[12pt, letterpaper]{article}" << std::endl
         << std::endl
         << std::endl
         << "\\usepackage{graphicx}" << std::endl
         << "\\graphicspath{{.}}" << std::endl
         << std::endl
         << "\\usepackage{amsmath}" << std::endl
         << std::endl
         << extra
         << std::endl
         << "\\begin{document}" << std::endl
         << std::endl
         << std::endl
         << "\\maketitle" << std::endl
         << std::endl
         << std::endl;
    return head.str();
}

// We also include a unit test for our helper method.
TEST(ParserTest, BuildDocumentHead)
{
    // The expected method output.
    std::stringstream expected;
    expected << "\\title{Lecture Notes}" << std::endl
             << "\\author{John Doe}" << std::endl
             << "\\date{2021-11-02}" << std::endl
             << std::endl
             << "\\documentclass[12pt, letterpaper]{article}" << std::endl
             << std::endl
             << std::endl
             << "\\usepackage{graphicx}" << std::endl
             << "\\graphicspath{{.}}" << std::endl
             << std::endl
             << "\\usepackage{amsmath}" << std::endl
             << std::endl
             << "\\usepackage{tabularx}" << std::endl
             << std::endl
             << std::endl
             << "\\begin{document}" << std::endl
             << std::endl
             << std::endl
             << "\\maketitle" << std::endl
             << std::endl
             << std::endl;

    std::stringstream extra;
    extra << "\\usepackage{tabularx}" << std::endl
          << std::endl;

    // The actual method output.
    std::string actual = build_document_head("Lecture Notes", "John Doe", "2021-11-02", extra.str());

    EXPECT_EQ(expected.str(), actual);
}

// Test the Parser class's method parse().
// Ensure that the method returns the correct header with the correct defaults.
TEST(ParserHeader, Defaults)
{
    sparkdown::Parser parser;

    std::string expected = build_document_head();

    std::string actual = parser.parse("");

    EXPECT_EQ(expected, actual);
}

// Test the Parser class's method parse().
// Ensure that the method returns the correct header with overridden defaults.
TEST(ParserHeader, Overrides)
{
    sparkdown::Parser parser;

    std::stringstream extra;
    extra << "\\usepackage{tabularx}" << std::endl
          << std::endl;

    std::string expected = build_document_head("Lecture Notes", "John Doe", "2021-11-02", extra.str());

    std::stringstream actual;
    actual << parser.parse("$title: Lecture Notes") << std::endl
           << parser.parse("$author: John Doe") << std::endl
           << parser.parse("$date: 2021-11-02") << std::endl
           << parser.parse("$usepackage: tabularx") << std::endl;

    EXPECT_EQ(expected, actual.str());
}

// Test the Parser class's method parse().
// From the language specifications, anything after a line of three or more equals signs or dashes
// should not be treated as a header.
TEST(ParserHeader, EndHeaderSignal)
{
    std::stringstream expected;
    expected << build_document_head("")
             << "$date: 2021-11-02$" << std::endl;

    // Test with three dashes.
    sparkdown::Parser parser;
    std::stringstream actual;
    actual << parser.parse("---") << std::endl
           << parser.parse("$date: 2021-11-02$");

    EXPECT_EQ(expected.str(), actual.str());

    // Same thing, but with equals signs.
    parser = sparkdown::Parser();
    actual.str("");
    actual << parser.parse("===") << std::endl
           << parser.parse("$date: 2021-11-02$");

    EXPECT_EQ(expected.str(), actual.str());

    // Same thing, but with five dashes instead of three.
    parser = sparkdown::Parser();
    actual.str("");
    actual << parser.parse("-----") << std::endl
           << parser.parse("$date: 2021-11-02$");

    EXPECT_EQ(expected.str(), actual.str());
}

// Test the Parser class's method parse().
// Ensure that the method correctly ends a header upon any line that does not start with a dollar sign.
TEST(ParserHeader, EndHeaderNoSignal)
{
    sparkdown::Parser parser;

    std::stringstream expected;
    expected << build_document_head() << "date: 2021-11-02" << std::endl;

    std::stringstream actual;
    actual << parser.parse("date: 2021-11-02") << std::endl;

    EXPECT_EQ(expected.str(), actual.str());
}

// Test the Parser class's stream extraction operator.
// Ensure that the method correctly returns a header, just as the parse() method does.
TEST(ParserHeader, Stream)
{
    sparkdown::Parser parser;

    std::stringstream input;
    input << "$date: 2021-11-02" << std::endl;

    std::stringstream expected;
    expected << build_document_head("Notes", "", "2021-11-02") << std::endl;

    input >> parser;

    std::stringstream actual;
    actual << parser;

    EXPECT_EQ(expected.str(), actual.str());
}
