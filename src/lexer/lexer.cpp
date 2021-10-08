// src/lexer/lexer.cpp
// v. 0.1.1
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
#include <vector>

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// We use the Token class to build a vector of tokens.
#include "lexer/token/token.hpp"

// The header for the Lexer class.
#include "lexer.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

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
    std::vector<mark_sideways::Token> mark_sideways::Lexer::lex(std::string line)
    {
        std::vector<mark_sideways::Token> tokens;
        tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, line));
        return tokens;
    }

    // A helper method to lex a line from the head of the file.
    //
    // * std::string line                         - The line to lex.
    // * return std::vector<mark_sideways::Token> - The vector of tokens.
    std::vector<mark_sideways::Token> mark_sideways::Lexer::lex_head(std::string line)
    {
    }

    // A recursive helper method to lex a line from the body of the file.
    //
    // * std::vector<mark_sideways::Token> &tokens - The vector of tokens.
    void mark_sideways::Lexer::lex_body(std::vector<mark_sideways::Token> &tokens)
    {
    }
}
