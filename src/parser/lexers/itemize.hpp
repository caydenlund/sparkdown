// src/lib/parser/lexers/itemize.hpp
// v. 0.1.1
//
// Author: Cayden Lund
//   Date: 10/06/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the bullet point lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef BULLETS_HPP
#define BULLETS_HPP

#include <string>
#include <regex>

#include "parser/state.hpp"
#include "parser/lexer.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // The lexers namespace contains all the lexer classes.
    namespace lexers
    {
        // Itemize.
        // This class is used to lex bullet points.
        class Itemize : public Lexer
        {
        public:
            // The constructor saves a reference to the State object, which is used to store
            // the current state of the parser.
            //
            // * mark_sideways::State state - The state object.
            Itemize(mark_sideways::State *state);

            // The class destructor.
            virtual ~Itemize();

            // Returns true when a given line is a bullet point.
            //
            // * std::string line - The line to check.
            // * return bool      - True if the line is a bullet point.
            bool is_bullet_point(std::string line);

            // lex() is used to lex a single input line.
            // This method takes in a string and returns a new string with the lexed tokens.
            //
            // * std::string line   - The string to lex.
            // * return std::string - The lexed string.
            std::string lex(std::string line);

        private:
            // ignore() returns true when we should ignore the given line.
            //
            // * std::string line - The line to test.
            // * return bool      - Whether we should ignore the given line.
            bool ignore(std::string line);

            // Used to construct the token used to replace the bullet point.
            // The token is of the form "[%%==BULLET_{LEVEL}==%%]", where {LEVEL} is the bullet point level.
            //
            // * int level - The level of the bullet point.
            std::string get_token(int level);

            // The regex used to lex bullet points.
            std::regex match_regex;

            // The regex used to lex escaped bullet points.
            std::regex escape_regex;
        };
    }
}

#endif