// //parser
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the Parser class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#ifndef PARSER_HPP
#define PARSER_HPP

// System imports.
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>

// We use the Token class to represent a single token.
#include "token/token.hpp"

namespace sparkdown
{
    // Parser
    //    Used to parse a string of sparkdown into a string of LaTeX.
    //
    //    There are two ways to use the Parser class:
    //       1. Use the parse() method:
    //             Parser parser;
    //             std::string latex = parser.parse("# Hello, World!") + parser.end();
    //       2. Use the stream operators:
    //             Parser parser;
    //             std::stringstream ss;
    //             "# Hello, World!" >> parser;
    //             ss << parser << parser.end();
    //             std::string latex = ss.str();
    class Parser
    {
    public:
        // constructor
        //    Takes no arguments.
        Parser();

        // parse
        //    Takes a string of sparkdown and returns a string of LaTeX.
        //
        // Arguments:
        //    const std::string &line - The string of sparkdown to parse.
        //
        // Returns:
        //    std::string - The string of LaTeX.
        std::string parse(const std::string &input);

        // operator >>
        //    The stream operator for parsing.
        //
        // Example:
        //    Parser parser;
        //    "# Hello, World!" >> parser;
        //
        // Parameters:
        //    std::istream &is - The input stream.
        //    Parser &parser   - The parser in action.
        //
        // Returns:
        //    std::istream & - The input stream.
        friend std::istream &operator>>(std::istream &is, Parser &parser);

        // operator <<
        //    The stream operator for output.
        //
        // Example:
        //    Parser parser;
        //    // ...
        //    std::cout << parser << parser.end();
        //
        // Parameters:
        //    std::ostream &os     - The output stream.
        //    const Parser &parser - The parser in action.
        //
        // Returns:
        //    std::ostream & - The output stream.
        friend std::ostream &operator<<(std::ostream &os, const Parser &parser);

        // is_head
        //    Indicates whether or not we are still parsing the head of the document.
        //
        // Returns:
        //    bool - True when we are still parsing the head of the document.
        bool is_head();

        // end
        //    Indicates to the parser that the file has finished being read.
        //
        // Returns:
        //    std::string - The ending LaTeX (including the `\end{document}`).
        std::string end();

    private:
        // parse
        //    Parses the given vector of tokens.
        //
        // Arguments:
        //    std::vector<Token> &tokens - The vector of tokens to parse.
        //
        // Returns:
        //    std::string - The LaTeX.
        std::string parse(std::vector<Token> &tokens);

        // set_property
        //    Sets a property of the document.
        //
        // Arguments:
        //    const std::string &property - The property to set.
        //    const std::string &value    - The new value of the property.
        void set_property(const std::string &property, const std::string &value);

        // escape_next
        //    In a given vector of tokens, deletes the token at the given index
        //    and escapes the following token.
        //
        // Arguments:
        //    std::vector<Token> &tokens - The vector of tokens.
        //    const size_t &index        - The index of the token to escape.
        static void escape_next(std::vector<Token> &tokens, size_t index);

        // The object that holds the unflushed LaTeX.
        // Here, "unflushed" refers to the LaTeX that has not been written to the output stream.
        std::stringstream latex;

        // Whether we have yet flushed the beginning and end of the output.
        bool flushed_beginning;
        bool flushed_end;

        // Whether we are still in the head of the document.
        bool in_head;

        // Whether we are currently parsing math text.
        bool in_block_math;
        bool in_inline_math;

        // Whether we are currently parsing verbatim text.
        bool in_block_verbatim;
        bool in_inline_verbatim;

        // The author of the document.
        std::string author;

        // The title of the document.
        std::string title;

        // The date of the document.
        std::string date;

        // The packages used by the document.
        std::set<std::string> packages;
    };
}

#endif