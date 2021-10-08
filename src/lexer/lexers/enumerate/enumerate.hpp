// src/lexer/lexers/enumerate/enumerate.hpp
// v. 0.3.0
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the enumerate lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef ENUMERATE_HPP
#define ENUMERATE_HPP

// System imports.
#include <string>
#include <regex>
#include <vector>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

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
        // Enumerate.
        // This class is used to lex bullet points.
        class Enumerate : public AbstractLexer
        {
        public:
            // The constructor saves a reference to the State object, which is used to store
            // the current state of the parser.
            //
            // * mark_sideways::State state - The state object.
            Enumerate(mark_sideways::State *state);

            // The class destructor.
            virtual ~Enumerate();

            // Returns true when a given line is a bullet point.
            //
            // * std::string line - The line to check.
            // * return bool      - True if the line is a bullet point.
            bool is_enumerate(std::string line);

            // lex() is used to lex a single input line.
            // This method takes in a string and returns a new vector with the lexed tokens.
            //
            // * std::string line                         - The string to lex.
            // * return std::vector<mark_sideways::Token> - The vector of tokens.
            std::vector<mark_sideways::Token> lex(std::string line);

        private:
            // The regex used to lex bullet points.
            std::regex match_regex;

            // The regex used to lex escaped bullet points.
            std::regex escape_regex;
        };
    }
}

#endif