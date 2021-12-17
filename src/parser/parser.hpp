// //parser
// v. 0.7.0
//
// Author: Cayden Lund
//   Date: 11/02/2021
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
#include <sstream>
#include <iostream>
#include <set>

// We use the Token class to represent a single token.
#include "token/token.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The Parser class is the class used to parse a string of sparkdown
    // into a string of LaTeX.
    //
    // There are two ways to use the Parser class.
    //
    //   1. Use the parse() method:
    //
    //        Parser parser;
    //        std::string latex = parser.parse("# Hello, World!");
    //
    //   2. Use the << operator:
    //
    //        Parser parser;
    //        std::stringstream ss;
    //        "# Hello, World!" >> parser;
    //        ss << parser;
    //        std::string latex = ss.str();
    class Parser
    {
    public:
        // The class constructor.
        Parser();

        // Parse the given string.
        //
        // * const std::string &input - The string to parse.
        // * return std::string       - The parsed string.
        std::string parse(const std::string &input);

        // The input stream operator.
        //
        //   Parser parser;
        //   "# Hello, World!" >> parser;
        //
        // * std::istream &in     - The input stream.
        // * Parser &parser       - The parser.
        // * return std::istream& - The input stream.
        friend std::istream &operator>>(std::istream &is, Parser &parser);

        // The output stream operator.
        //
        //   Parser parser;
        //   // ...
        //   std::cout << parser;
        //
        // * std::ostream &out    - The output stream.
        // * const Parser &parser - The parser.
        // * return std::ostream& - The output stream.
        friend std::ostream &operator<<(std::ostream &os, const Parser &parser);

        // Indicates whether we are still parsing the head of the document.
        //
        // * return bool - True when we are still parsing the head of the document.
        bool is_head();

        // Indicate to the parser that the file has finished parsing.
        //
        // * return std::string - The necessary \end{document} to be added to the foot of the output.
        std::string end();

    private:
        // Parse the given vector of tokens.
        //
        // * std::vector<Token> &tokens - The vector of tokens.
        // * return std::string         - The parsed string.
        std::string parse(std::vector<Token> &tokens);

        // Set a property.
        // Used by header commands.
        //
        // * const std::string &property - The property to set.
        // * const std::string &value    - The new value of the property.
        void set_property(const std::string &property, const std::string &value);

        // Consolidate the given vector of tokens.
        // Concatenate adjacent corresponding tokens into one.
        //
        // * std::vector<Token> &tokens - The vector of tokens.
        static void consolidate(std::vector<Token> &tokens);

        // In a given vector of tokens, check whether the token at the given index
        // and the following token are both of the given type.
        // If they are, concatenate them into one token.
        //
        // * std::vector<Token> &tokens - The vector of tokens.
        // * const size_t &index        - The index of the token to merge.
        // * const token_type &type     - The type of the token to check.
        static void merge_next(std::vector<Token> &tokens, const size_t &index, const token_type &type);

        // In a given vector of tokens, delete the token at the given index
        // and escape the following token.
        //
        // * std::vector<Token> &tokens - The vector of tokens.
        // * size_t index               - The index of the token to delete.
        static void escape_next(std::vector<Token> &tokens, size_t index);

        // The object that holds the unflushed LaTeX.
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