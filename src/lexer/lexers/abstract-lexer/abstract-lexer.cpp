// src/lexer/lexers/abstract-lexer.cpp
// v. 0.6.2
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
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
#include "state/state.hpp"

// The header for the AbstractLexer class.
#include "abstract-lexer.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
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
        // * sparkdown::State state - The state object.
        sparkdown::lexers::AbstractLexer::AbstractLexer(sparkdown::State *state)
        {
            this->state = state;
        }
    }
}
