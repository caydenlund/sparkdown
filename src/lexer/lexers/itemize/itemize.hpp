// //lexer/lexers/itemize
// v. 0.3.4
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the bullet point lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#ifndef ITEMIZE_HPP
#define ITEMIZE_HPP

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

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The lexers namespace contains all the sub-lexer classes.
    namespace lexers
    {
        // Itemize.
        // This class is used to lex bullet points.
        class Itemize : public AbstractLexer
        {
        public:
            // The constructor saves a reference to the State object, which is used to store
            // the current state of the parser.
            //
            // * sparkdown::State state - The state object.
            Itemize(sparkdown::State *state);

            // The class destructor.
            virtual ~Itemize();

            // Returns true when a given line is a bullet point.
            //
            // * const std::string &line - The line to check.
            // * return bool             - True if the line is a bullet point.
            bool is_bullet_point(const std::string &line);

            // lex() is used to lex a single input line.
            // This method takes in a string and returns a new vector with the lexed tokens.
            //
            // * const std::string &line                  - The string to lex.
            // * return std::vector<sparkdown::Token> - The vector of tokens.
            std::vector<sparkdown::Token> lex(const std::string &line);

        private:
            // The regex used to lex bullet points.
            std::regex match_regex;

            // The regex used to lex escaped bullet points.
            std::regex escape_regex;
        };
    }
}

#endif