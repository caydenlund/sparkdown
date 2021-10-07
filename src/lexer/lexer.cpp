// src/lexer/lexer.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the Lexer class.
// This class is used to lex a line for parsing.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

// The header for the Lexer class.
#include "lexer.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstractLexer/abstractLexer.hpp"

// The various sub-lexers.
#include "lexer/lexers/enumerate/enumerate.hpp"
#include "lexer/lexers/itemize/itemize.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // The class constructor.
    //
    // * mark_sideways::State *state - The State object to use for keeping track of the state of the parser.
    mark_sideways::Lexer::Lexer(mark_sideways::State *state) : mark_sideways::lexers::AbstractLexer(state)
    {
        this->enumerate = new mark_sideways::lexers::Enumerate(state);
        this->itemize = new mark_sideways::lexers::Itemize(state);
    }

    // The class destructor.
    mark_sideways::Lexer::~Lexer()
    {
        delete this->enumerate;
        delete this->itemize;
    }

    // lex() is used to lex a single input line.
    // This method takes in a string and returns a new string with the lexed tokens.
    //
    // * std::string line   - The line to lex.
    // * return std::string - The lexed line.
    std::string mark_sideways::Lexer::lex(std::string line)
    {
        line = this->enumerate->lex(line);
        line = this->itemize->lex(line);
        return line;
    }
}
