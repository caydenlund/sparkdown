// src/lexer/lexers/header/header.hpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the bullet point lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef HEADER_HPP
#define HEADER_HPP

// System imports.
#include <string>
#include <regex>
#include <vector>

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// We use the Token class to build a vector of tokens.
#include "lexer/token/token.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // The lexers namespace contains all the sub-lexer classes.
    namespace lexers
    {
        // Header.
        // This class is used to lex metadata at the head of a mark-sideways document.
        class Header : public AbstractLexer
        {
        public:
            // The constructor saves a reference to the State object, which is used to store
            // the current state of the parser.
            //
            // * mark_sideways::State state - The state object.
            Header(mark_sideways::State *state);

            // The class destructor.
            virtual ~Header();

            // lex() is used to lex a single input line.
            // This method takes in a string and returns a new vector with the lexed tokens.
            //
            // * std::string line                         - The string to lex.
            // * return std::vector<mark_sideways::Token> - The vector of tokens.
            std::vector<mark_sideways::Token> lex(std::string line);

        private:
            // The regex used to lex the header line.
            std::regex match_regex;

            // The regex used to lex an escaped header.
            std::regex escape_regex;

            // The regex used to check whether a line is whitespace.
            std::regex whitespace_regex;

            // The regex used to check for a line of '=' characters.
            std::regex equals_regex;
        };
    }
}

#endif