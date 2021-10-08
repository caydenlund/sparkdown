// src/parser/parser-test.cpp
// v. 0.3.1
//
// Author: Cayden Lund
//   Date: 10/07/2021
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

#include "parser.hpp"

using namespace mark_sideways;

// Test the Parser::Parser() zero-argument constructor.
// This test is expected to pass unless the constructor throws an exception.
TEST(Parser, Constructor)
{
    Parser parser = Parser();
}

// Test the Parser#start() method.
// This test ensures that the start() method returns the correct value with
// everything left as default.
TEST(Parser, StartDefaults)
{
    Parser parser = Parser();

    std::stringstream expected;
    expected << "\\title{Notes}" << std::endl;
    expected << "\\author{Cayden Lund}" << std::endl;
    expected << "\\date{}" << std::endl;
    expected << std::endl;
    expected << "\\documentclass[12pt, letterpaper]{article}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\usepackage{graphicx}" << std::endl;
    expected << "\\graphicspath{{.}}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage[utf8]{inputenc}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{tabularx}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{amsmath}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\begin{document}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\maketitle" << std::endl;
    expected << std::endl;

    std::string actual = parser.start();

    EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#start() method.
// This test ensures that the start() method returns the correct value with
// default values for the title, author, and date overridden.
TEST(Parser, StartOverrides)
{
    Parser parser = Parser();

    parser.parse_line("$title: My Notes");
    parser.parse_line("$author: Test");
    parser.parse_line("$date: Date");

    std::stringstream expected;
    expected << "\\title{My Notes}" << std::endl;
    expected << "\\author{Test}" << std::endl;
    expected << "\\date{Date}" << std::endl;
    expected << std::endl;
    expected << "\\documentclass[12pt, letterpaper]{article}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\usepackage{graphicx}" << std::endl;
    expected << "\\graphicspath{{.}}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage[utf8]{inputenc}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{tabularx}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{amsmath}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\begin{document}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\maketitle" << std::endl;
    expected << std::endl;

    std::string actual = parser.start();

    EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#start() method.
// This test ensures that the start() method returns the correct value with
// extra packages added.
TEST(Parser, StartPackages)
{
    Parser parser = Parser();

    parser.parse_line("$usepackage: xcolor");
    parser.parse_line("$usepackage: geometry");

    std::stringstream expected;
    expected << "\\title{Notes}" << std::endl;
    expected << "\\author{Cayden Lund}" << std::endl;
    expected << "\\date{}" << std::endl;
    expected << std::endl;
    expected << "\\documentclass[12pt, letterpaper]{article}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\usepackage{graphicx}" << std::endl;
    expected << "\\graphicspath{{.}}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage[utf8]{inputenc}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{tabularx}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{amsmath}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{xcolor}" << std::endl;
    expected << std::endl;
    expected << "\\usepackage{geometry}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\begin{document}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\maketitle" << std::endl;
    expected << std::endl;

    std::string actual = parser.start();

    EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#end() method.
// This test ensures that the end() method returns the correct value with
// everything left as default.
TEST(Parser, EndDefaults)
{
    Parser parser = Parser();

    std::string expected = "\n\n\\end{document}";

    std::string actual = parser.end();

    EXPECT_EQ(expected, actual);
}

// Test the Parser#end() method.
// This test ensures that the end() method returns the correct value with
// a closing of itemize and enumerate.
TEST(Parser, EndLists)
{
    Parser parser = Parser();

    parser.parse_line("* Itemize 1.\n");
    parser.parse_line("  * Itemize 2.\n");
    parser.parse_line("    1. Enumerate.\n");

    std::stringstream expected;
    expected << "        \\end{enumerate}" << std::endl;
    expected << "    \\end{itemize}" << std::endl;
    expected << "\\end{itemize}" << std::endl;
    expected << std::endl;
    expected << std::endl;
    expected << "\\end{document}";

    std::string actual = parser.end();

    EXPECT_EQ(expected.str(), actual);
}

// Test the Parser#parse_line() method.
// This test is expected to pass unless the method throws an exception.
TEST(Parser, ParseLine)
{
    Parser parser = Parser();
    parser.parse_line("This is unformatted text.");
}

// Test the Parser#parse_line() method.
// This test ensures that unformatted text is correctly returned unmodified.
TEST(Parser, UnformattedText)
{
    Parser parser = Parser();
    std::string input = "This is unformatted text.";
    std::string output = parser.parse_line(input);
    EXPECT_EQ(input, output);
}

// Test the Parser#parse_line() method.
// This test ensures that a section header is correctly returned in LaTeX format.
TEST(Parser, SectionHeader)
{
    Parser parser = Parser();
    std::string input = "# This is a section header.";
    std::string output = parser.parse_line(input);
    std::string expected = "\\section*{This is a section header.}";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that a section header is correctly returned in LaTeX format.
// This test also ensures that symbols inside of the header are unmodified.
TEST(Parser, SectionHeaderWithSymbols)
{
    Parser parser = Parser();
    std::string input = "# This is a section header with symbols: #, *, and _.";
    std::string output = parser.parse_line(input);
    std::string expected = "\\section*{This is a section header with symbols: #, *, and _.}";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "# This is a section header with symbols: *nonitalic text.*";
    output = parser.parse_line(input);
    expected = "\\section*{This is a section header with symbols: *nonitalic text.*}";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "# This is a section header with symbols: ->";
    output = parser.parse_line(input);
    expected = "\\section*{This is a section header with symbols: ->}";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that a single bullet point is correctly returned in LaTeX format.
TEST(Parser, SingleBulletPoint)
{
    Parser parser = Parser();

    std::string input = "* This is a bullet point.";

    std::string output = parser.parse_line(input);

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point.";

    EXPECT_EQ(expected.str(), output);

    parser = Parser();

    input = "- This is a bullet point.";

    output = parser.parse_line(input);

    expected = std::stringstream();
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point.";

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that a set of two equally-nested bullet points
// is correctly returned in LaTeX format.
TEST(Parser, MultipleEqualBulletPoints)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "* This is a bullet point." << std::endl;

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "* This is a second bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\item This is a second bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    parser = Parser();

    input = std::stringstream();
    input << "- This is a bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "- This is a second bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\item This is a second bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that a sub-bullet point is correctly returned in LaTeX format.
TEST(Parser, SubBulletPoint)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "* This is a bullet point." << std::endl;

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "  * This is a sub-bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\begin{itemize}" << std::endl;
    expected << "        \\item This is a sub-bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    parser = Parser();

    input = std::stringstream();
    input << "- This is a bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "  - This is a sub-bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\begin{itemize}" << std::endl;
    expected << "        \\item This is a sub-bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that the parser can enter a sub-bullet point list
// and then exit from it.
TEST(Parser, SubBulletPointExit)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "* This is a bullet point." << std::endl;

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "  * This is a sub-bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\begin{itemize}" << std::endl;
    expected << "        \\item This is a sub-bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "* This is another top-level bullet point.";

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\end{itemize}" << std::endl;
    expected << "    \\item This is another top-level bullet point.";

    EXPECT_EQ(expected.str(), output);

    parser = Parser();

    input = std::stringstream();
    input << "- This is a bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "\\begin{itemize}" << std::endl;
    expected << "    \\item This is a bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "  - This is a sub-bullet point." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\begin{itemize}" << std::endl;
    expected << "        \\item This is a sub-bullet point." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "- This is another top-level bullet point.";

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\end{itemize}" << std::endl;
    expected << "    \\item This is another top-level bullet point.";

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that an escaped bullet point is unmodified.
TEST(Parser, EscapedBulletPoint)
{
    Parser parser = Parser();
    std::string input = "\\* This is an escaped bullet point.";
    std::string output = parser.parse_line(input);
    std::string expected = "* This is an escaped bullet point.";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "\\- This is an escaped bullet point.";
    output = parser.parse_line(input);
    expected = "- This is an escaped bullet point.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that a bullet point in math mode is unmodified.
TEST(Parser, BulletPointInMathMode)
{
    Parser parser = Parser();
    parser.parse_line("$$");
    std::string input = "* This is a bullet point in math mode.";
    std::string output = parser.parse_line(input);
    std::string expected = "* This is a bullet point in math mode.";
    EXPECT_EQ(expected, output);

    parser = Parser();
    parser.parse_line("\\[");
    input = "* This is a bullet point in math mode.";
    output = parser.parse_line(input);
    expected = "* This is a bullet point in math mode.";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "$* Bullet point.$";
    output = parser.parse_line(input);
    expected = "$* Bullet point.$";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "\\[* Bullet point.\\]";
    output = parser.parse_line(input);
    expected = "\\[* Bullet point.\\]";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "$$* Bullet point.$$";
    output = parser.parse_line(input);
    expected = "$$* Bullet point.$$";
    EXPECT_EQ(expected, output);

    parser = Parser();
    parser.parse_line("$$");
    input = "- This is a bullet point in math mode.";
    output = parser.parse_line(input);
    expected = "- This is a bullet point in math mode.";
    EXPECT_EQ(expected, output);

    parser = Parser();
    parser.parse_line("\\[");
    input = "- This is a bullet point in math mode.";
    output = parser.parse_line(input);
    expected = "- This is a bullet point in math mode.";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "$- Bullet point.$";
    output = parser.parse_line(input);
    expected = "$- Bullet point.$";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "\\[- Bullet point.\\]";
    output = parser.parse_line(input);
    expected = "\\[- Bullet point.\\]";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "$$- Bullet point.$$";
    output = parser.parse_line(input);
    expected = "$$- Bullet point.$$";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that a single enumerated item is correctly returned in LaTeX format.
TEST(Parser, SingleEnumerate)
{
    Parser parser = Parser();

    std::string input = "1. This is an enumerated item.";

    std::string output = parser.parse_line(input);

    std::stringstream expected;
    expected << "\\begin{enumerate}" << std::endl;
    expected << "    \\item This is an enumerated item.";

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that a set of two equally-nested enumerated items
// is correctly returned in LaTeX format.
TEST(Parser, MultipleEqualEnumeratedItems)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "1. This is an enumerated item." << std::endl;

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{enumerate}" << std::endl;
    expected << "    \\item This is an enumerated item." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "2. This is a second enumerated item." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\item This is a second enumerated item." << std::endl;

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that a sub-enumerated item is correctly returned in LaTeX format.
TEST(Parser, SubEnumeratedItem)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "1. This is an enumerated item." << std::endl;

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{enumerate}" << std::endl;
    expected << "    \\item This is an enumerated item." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "  1. This is a sub-enumerated item." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\begin{enumerate}" << std::endl;
    expected << "        \\item This is a sub-enumerated item." << std::endl;

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that the parser can enter a sub-enumerated list
// and then exit from it.
TEST(Parser, SubEnumeratedItemExit)
{
    Parser parser = Parser();

    std::stringstream input;
    input << "1. This is an enumerated item." << std::endl;

    std::string output = parser.parse_line(input.str());

    std::stringstream expected;
    expected << "\\begin{enumerate}" << std::endl;
    expected << "    \\item This is an enumerated item." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "  1. This is a sub-enumerated item." << std::endl;

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\begin{enumerate}" << std::endl;
    expected << "        \\item This is a sub-enumerated item." << std::endl;

    EXPECT_EQ(expected.str(), output);

    input = std::stringstream();
    input << "2. This is another top-level enumerated item.";

    output = parser.parse_line(input.str());

    expected = std::stringstream();
    expected << "    \\end{enumerate}" << std::endl;
    expected << "    \\item This is another top-level enumerated item.";

    EXPECT_EQ(expected.str(), output);
}

// Test the Parser#parse_line() method.
// This test ensures that a enumerated item in math mode is unmodified.
TEST(Parser, EnumeratedItemInMathMode)
{
    Parser parser = Parser();
    parser.parse_line("$$");
    std::string input = "1. This is a enumerated item in math mode.";
    std::string output = parser.parse_line(input);
    std::string expected = "1. This is a enumerated item in math mode.";
    EXPECT_EQ(expected, output);

    parser = Parser();
    parser.parse_line("\\[");
    input = "1. This is a enumerated item in math mode.";
    output = parser.parse_line(input);
    expected = "1. This is a enumerated item in math mode.";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "$1. Enumerated item.$";
    output = parser.parse_line(input);
    expected = "$1. Enumerated item.$";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "\\[1. Enumerated item.\\]";
    output = parser.parse_line(input);
    expected = "\\[1. Enumerated item.\\]";
    EXPECT_EQ(expected, output);

    parser = Parser();
    input = "$$1. Enumerated item.$$";
    output = parser.parse_line(input);
    expected = "$$1. Enumerated item.$$";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that little rightarrows are correctly converted to LaTeX format.
TEST(Parser, LittleRightArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a right arrow ->.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a right arrow $\\rightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with a right arrow -->.";
    output = parser.parse_line(input);
    expected = "This is another sentence with a right arrow $\\longrightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a right arrow in math mode $->$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a right arrow in math mode $\\rightarrow$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that big rightarrows are correctly converted to LaTeX format.
TEST(Parser, BigRightArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a big right arrow =>.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a big right arrow $\\Rightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with a big right arrow ==>.";
    output = parser.parse_line(input);
    expected = "This is another sentence with a big right arrow $\\Longrightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a big right arrow in math mode $==>$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a big right arrow in math mode $\\Longrightarrow$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped rightarrows are unchanged.
TEST(Parser, EscapedRightArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped right arrow \\->.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped right arrow \\->.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with an escaped right arrow \\==>.";
    output = parser.parse_line(input);
    expected = "This is another sentence with an escaped right arrow \\==>.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with an escaped right arrow in math mode $\\==>$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with an escaped right arrow in math mode $\\==>$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that little leftarrows are correctly converted to LaTeX format.
TEST(Parser, LittleLeftArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a left arrow <-.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a left arrow $\\leftarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with a left arrow <--.";
    output = parser.parse_line(input);
    expected = "This is another sentence with a left arrow $\\longleftarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a left arrow in math mode $<-$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a left arrow in math mode $\\leftarrow$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that big leftarrows are correctly converted to LaTeX format.
TEST(Parser, BigLeftArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a big left arrow <=.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a big left arrow $\\Leftarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with a big left arrow <==.";
    output = parser.parse_line(input);
    expected = "This is another sentence with a big left arrow $\\Longleftarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a big left arrow in math mode $<==$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a big left arrow in math mode $\\Longleftarrow$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped leftarrows are unchanged.
TEST(Parser, EscapedLeftArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped left arrow \\<-.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped left arrow \\<-.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with an escaped left arrow \\<==.";
    output = parser.parse_line(input);
    expected = "This is another sentence with an escaped left arrow \\<==.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with an escaped left arrow in math mode $\\<==$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with an escaped left arrow in math mode $\\<==$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that little doublearrows are correctly converted to LaTeX format.
TEST(Parser, LittleDoubleArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a double arrow <->.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a double arrow $\\leftrightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with a double arrow <-->.";
    output = parser.parse_line(input);
    expected = "This is another sentence with a double arrow $\\longleftrightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a double arrow in math mode $<->$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a double arrow in math mode $\\leftrightarrow$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that big doublearrows are correctly converted to LaTeX format.
TEST(Parser, BigDoubleArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a big double arrow <=>.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a big double arrow $\\Leftrightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with a big double arrow <==>.";
    output = parser.parse_line(input);
    expected = "This is another sentence with a big double arrow $\\Longleftrightarrow$.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a big double arrow in math mode $<==>$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a big double arrow in math mode $\\Leftrightarrow$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped doublearrows are unchanged.
TEST(Parser, EscapedDoubleArrow)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped double arrow \\<->.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped double arrow \\<->.";
    EXPECT_EQ(expected, output);

    input = "This is another sentence with an escaped double arrow \\<==>.";
    output = parser.parse_line(input);
    expected = "This is another sentence with an escaped double arrow \\<==>.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with an escaped double arrow in math mode $\\<==>$.";
    output = parser.parse_line(input);
    expected = "This is a sentence with an escaped double arrow in math mode $\\<==>$.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that symbols are not converted to LaTeX format inside of inline math mode.
TEST(Parser, InlineMathNoSymbols)
{
    Parser parser = Parser();

    std::string input = "This is a formula with a symbol: $*text*$.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a symbol: $*text*$";

    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that symbols are not converted to LaTeX format inside of display math mode.
TEST(Parser, DisplayMathNoSymbols)
{
    Parser parser = Parser();

    std::string input = "$$*text*$$";
    std::string output = parser.parse_line(input);
    std::string expected = "$$*text*$$";
    EXPECT_EQ(expected, output);

    input = "\\[*text*\\]";
    output = parser.parse_line(input);
    expected = "\\[*text*\\]";
    EXPECT_EQ(expected, output);

    parser.parse_line("\\[\n");
    input = "  *text*";
    output = parser.parse_line(input);
    expected = "  *text*";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that >= symbols are converted to LaTeX format.
TEST(Parser, GreaterThanEqual)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a >= symbol.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a $\\geq$ symbol.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a $>=$ symbol in math mode.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a $\\geq$ symbol in math mode.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped >= symbols are unchanged.
TEST(Parser, EscapedGreaterThanEqual)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped \\>= symbol.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped >= symbol.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with an escaped $\\>=$ symbol in math mode.";
    output = parser.parse_line(input);
    expected = "This is a sentence with an escaped $>=$ symbol in math mode.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that <= symbols are converted to LaTeX format.
TEST(Parser, LessThanEqual)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a <= symbol.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a $\\leq$ symbol.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a $<=$ symbol in math mode.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a $\\leq$ symbol in math mode.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped <= symbols are unchanged.
TEST(Parser, EscapedLessThanEqual)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped \\<= symbol.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped <= symbol.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with an escaped $\\<=$ symbol in math mode.";
    output = parser.parse_line(input);
    expected = "This is a sentence with an escaped $<=$ symbol in math mode.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that != symbols are converted to LaTeX format.
TEST(Parser, NotEqual)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with a != symbol.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with a $\\neq$ symbol.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with a $!=$ symbol in math mode.";
    output = parser.parse_line(input);
    expected = "This is a sentence with a $\\neq$ symbol in math mode.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped != symbols are unchanged.
TEST(Parser, EscapedNotEqual)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped \\!= symbol.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped != symbol.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with an escaped $\\!=$ symbol in math mode.";
    output = parser.parse_line(input);
    expected = "This is a sentence with an escaped $!=$ symbol in math mode.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that italic text is converted to LaTeX format.
TEST(Parser, ItalicText)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with italic text.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with \\textit{italic} text.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped italic text is unchanged.
TEST(Parser, EscapedItalicText)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped \\*italic\\* text.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped *italic* text.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that bold text is converted to LaTeX format.
TEST(Parser, BoldText)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with **bold** text.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with \\textbf{bold} text.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that escaped bold text is unchanged.
TEST(Parser, EscapedBoldText)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped \\**bold\\** text.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped **bold** text.";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures that inline verbatim blocks are converted to LaTeX format.
TEST(Parser, VerbatimBlocks)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with |verbatim| text.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with \\verb|verbatim| text.";
}

// Test the Parser#parse_line() method.
// This test ensures that escaped inline verbatim blocks are unchanged.
TEST(Parser, EscapedVerbatimBlocks)
{
    Parser parser = Parser();

    std::string input = "This is a sentence with an escaped \\|verbatim\\| text.";
    std::string output = parser.parse_line(input);
    std::string expected = "This is a sentence with an escaped |verbatim| text.";
    EXPECT_EQ(expected, output);

    input = "This is a sentence with an escaped |pipe \\|| inside verbatim text.";
    output = parser.parse_line(input);
    expected = "This is a sentence with an escaped \\verb|pipe \\|| inside verbatim text.";
}

// Test the Parser#parse_line() method.
// This test ensures that express verbatim blocks are converted to LaTeX format.
TEST(Parser, ExpressVerbatimBlocks)
{
    Parser parser = Parser();

    std::string input = "```";
    std::string output = parser.parse_line(input);
    std::string expected = "\\begin{verbatim}";
    EXPECT_EQ(expected, output);

    input = "int main(int argc, char *argv[])";
    output = parser.parse_line(input);
    expected = "int main(int argc, char *argv[])";
    EXPECT_EQ(expected, output);

    input = "{";
    output = parser.parse_line(input);
    expected = "{";
    EXPECT_EQ(expected, output);

    input = "    printf(\"Hello, world!\\n\");";
    output = parser.parse_line(input);
    expected = "    printf(\"Hello, world!\\n\");";
    EXPECT_EQ(expected, output);

    input = "}";
    output = parser.parse_line(input);
    expected = "}";
    EXPECT_EQ(expected, output);

    input = "```";
    output = parser.parse_line(input);
    expected = "\\end{verbatim}";
}

// Test the Parser#parse_line() method.
// This test ensures that symbols inside verbatim blocks are unchanged.
TEST(Parser, EscapedVerbatimBlocksSymbols)
{
    Parser parser = Parser();

    std::string input = "```";
    std::string output = parser.parse_line(input);
    std::string expected = "\\begin{verbatim}";
    EXPECT_EQ(expected, output);

    input = "*Non-italic text.*";
    output = parser.parse_line(input);
    expected = "*Non-italic text.*";
    EXPECT_EQ(expected, output);

    input = "->";
    output = parser.parse_line(input);
    expected = "->";
    EXPECT_EQ(expected, output);

    input = "* Not a bullet point.";
    output = parser.parse_line(input);
    expected = "* Not a bullet point.";
    EXPECT_EQ(expected, output);

    input = "```";
    output = parser.parse_line(input);
    expected = "\\end{verbatim}";
    EXPECT_EQ(expected, output);
}

// Test the Parser#parse_line() method.
// This test ensures ensures that the verbatim block is indented correctly
// when all lines inside are indented.
TEST(Parser, IndentedVerbatimBlocks)
{
    Parser parser = Parser();

    parser.parse_line("* Begin itemize.");

    std::string input = "    ```";
    std::string output = parser.parse_line(input);
    std::string expected = "    \\begin{verbatim}";
    EXPECT_EQ(expected, output);

    input = "    int main(int argc, char *argv[])";
    output = parser.parse_line(input);
    expected = "int main(int argc, char *argv[])";
    EXPECT_EQ(expected, output);

    input = "    {";
    output = parser.parse_line(input);
    expected = "{";
    EXPECT_EQ(expected, output);

    input = "        printf(\"Hello, world!\\n\");";
    output = parser.parse_line(input);
    expected = "    printf(\"Hello, world!\\n\");";
    EXPECT_EQ(expected, output);

    input = "    }";
    output = parser.parse_line(input);
    expected = "}";
    EXPECT_EQ(expected, output);

    input = "    ```";
    output = parser.parse_line(input);
    expected = "    \\end{verbatim}";
}

// Test the Parser#parse_line() method.
// This test ensures that the verbatim block is indented correctly
// when the lines inside are not indented.
TEST(Parser, NonIndentedVerbatimBlocks)
{
    Parser parser = Parser();

    parser.parse_line("* Begin itemize.");

    std::string input = "    ```";
    std::string output = parser.parse_line(input);
    std::string expected = "    \\begin{verbatim}";
    EXPECT_EQ(expected, output);

    input = "int main(int argc, char *argv[])";
    output = parser.parse_line(input);
    expected = "int main(int argc, char *argv[])";
    EXPECT_EQ(expected, output);

    input = "{";
    output = parser.parse_line(input);
    expected = "{";
    EXPECT_EQ(expected, output);

    input = "    printf(\"Hello, world!\\n\");";
    output = parser.parse_line(input);
    expected = "    printf(\"Hello, world!\\n\");";
    EXPECT_EQ(expected, output);

    input = "}";
    output = parser.parse_line(input);
    expected = "}";
    EXPECT_EQ(expected, output);

    input = "    ```";
    output = parser.parse_line(input);
    expected = "    \\end{verbatim}";
}

// Test the Parser#parse_line() method.
// This test ensures that levels of itemize are correctly closed
// before verbatim blocks are opened.
TEST(Parser, ItemizeLevelsVerbatimBlocks)
{
    Parser parser = Parser();

    parser.parse_line("* Begin itemize.");

    std::string input = "```";
    std::string output = parser.parse_line(input);
    std::string expected = "\\end{itemize}\n\\begin{verbatim}";
    EXPECT_EQ(expected, output);

    input = "int main(int argc, char *argv[])";
    output = parser.parse_line(input);
    expected = "int main(int argc, char *argv[])";
    EXPECT_EQ(expected, output);

    input = "{";
    output = parser.parse_line(input);
    expected = "{";
    EXPECT_EQ(expected, output);

    input = "    printf(\"Hello, world!\\n\");";
    output = parser.parse_line(input);
    expected = "    printf(\"Hello, world!\\n\");";
    EXPECT_EQ(expected, output);

    input = "}";
    output = parser.parse_line(input);
    expected = "}";
    EXPECT_EQ(expected, output);

    input = "```";
    output = parser.parse_line(input);
    expected = "\\end{verbatim}";
    EXPECT_EQ(expected, output);
}
