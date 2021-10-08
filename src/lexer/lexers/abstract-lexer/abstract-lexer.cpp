// src/lexer/lexers/abstract-lexer.cpp
// v. 0.6.0
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the AbstractLexer class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// We use the State object to keep track of the current state of the parser.
#include "parser/state.hpp"

// The header for the AbstractLexer class.
#include "abstract-lexer.hpp"

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

        // The constructor saves a reference to the State object, which is used to store
        // the current state of the parser.
        //
        // * mark_sideways::State state - The state object.
        mark_sideways::lexers::AbstractLexer::AbstractLexer(mark_sideways::State *state)
        {
            this->state = state;
        }
    }
}
