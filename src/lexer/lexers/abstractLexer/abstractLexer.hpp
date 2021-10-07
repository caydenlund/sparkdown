// src/lexer/lexers/abstractLexer.hpp
// v. 0.3.0
//
// Author: Cayden Lund
//   Date: 10/06/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the AbstractLexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef ABSTRACT_LEXER_HPP
#define ABSTRACT_LEXER_HPP

// System imports.
#include <string>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // The lexers namespace contains all the lexer classes.
    namespace lexers
    {
        // Lexer.
        // This class is the abstract lexer class, implemented by the various lexer classes.
        // These lexers are then used by the Parser class to parse the input line into tokens.
        // Lexers often include a regular expression to match the token.
        class AbstractLexer
        {
        public:
            // The constructor saves a reference to the State object, which is used to store
            // the current state of the parser.
            //
            // mark_sideways::State state - The state object.
            AbstractLexer(mark_sideways::State *state);

            // This method is the abstract lex() method, implemented by the various lexer classes.
            // This method takes in a string and returns a new string with the lexed tokens.
            //
            // * std::string line   - The string to lex.
            // * return std::string - The lexed string.
            virtual std::string lex(std::string line) = 0;

        protected:
            // The state object.
            mark_sideways::State *state;
        };
    }
}

#endif