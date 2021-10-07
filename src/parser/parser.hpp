// src/parser/parser.hpp
// v. 0.6.0
//
// Author: Cayden Lund
//   Date: 10/06/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the Parser class.
// See parser.cpp for implementation.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <regex>

// We use the State class to keep track of the current state of the parser.
#include "state.hpp"

// We use the Lexer class to lex a line into tokens.
#include "lexer/lexer.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // Parser.
    // This class is used to parse a set of strings formatted as mark-sideways into a set of strings of LaTeX.
    // The mark-sideways text is parsed line by line, and as we read each line, we update the state accordingly.
    // Upon reading the line, we use the state to determine what to do with the line.
    // We then return a string of LaTeX to the caller.
    //
    // The mark-sideways rules are as follows:
    //
    //   1.  #  A headline.
    //       ## A sub-headline.
    //   2.  *  A bullet point.
    //       -  A bullet point.
    //   3.  1. Item of a numbered list.
    //   4.  **Inline bold text.**
    //   5.  *Inline italic text.*
    //   6.  ```
    //       Block of verbatim text.
    //       ```
    //   7.  |Inline verbatim text.|
    //   8.  -> Rightarrow.
    //       => Rightarrow.
    class Parser
    {
    public:
        // The constructor for the Parser class.
        // It accepts no arguments and has some default values.
        // Overrides of these defaults are specified
        // inside the mark-sideways text itself.
        Parser();

        // The class destructor.
        ~Parser();

        // Returns the LaTeX headers for a new file,
        // using our `title`, `author`, and `date` instance variables.
        std::string start();

        // Returns the footers for a new file.
        std::string end();

        // Returns true while we are currently parsing the head of the file.
        bool is_head();

        // Parse a single line from the head of the file.
        //
        // * std::string line - The line to parse.
        void parse_headline(std::string line);

        // Parse a single line from the body of the file.
        //
        // * std::string line - The line to parse.
        std::string parse_line(std::string line);

    protected:
        // ====================
        // | Private methods. |
        // ====================

        // Parse headlines.
        void parse_section();

        // Parse indentation.
        void parse_indentation();

        // Parse bold text.
        void parse_bold();

        // Parse italic text.
        void parse_italics();

        // Parse inline verbatim text.
        void parse_verb();

        // Parse block verbatim text.
        void parse_verbatim();

        // Parse rightarrows.
        void parse_arrow();

        // =======================
        // | Instance variables. |
        // =======================

        // ===== Some regular expressions to match various things. =====

        std::regex headline_regex;
        std::regex title_regex;
        std::regex author_regex;
        std::regex date_regex;
        std::regex section_regex;
        std::regex indentation_regex;
        std::regex bold_regex;
        std::regex italic_regex;
        std::regex verb_regex;
        std::regex verbatim_regex;
        std::regex arrow_regex;
        std::regex section_char_regex;

        // ===== Misc. =====

        // The current state of the parser.
        State *state;

        // The line lexer.
        Lexer *lexer;

        // Whether or not we are currently parsing the head of the file.
        bool head;

        // The title of the document.
        std::string title;

        // The author of the document.
        std::string author;

        // The date of the document.
        std::string date;
    };
}

#endif