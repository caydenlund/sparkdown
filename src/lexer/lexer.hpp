// src/lexer/lexer.hpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the Lexer class.
// This class is used to lex a line for parsing.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef LEXER_HPP
#define LEXER_HPP

// System imports.
#include <string>
#include <regex>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstractLexer/abstractLexer.hpp"

// The various sub-lexers.
#include "lexer/lexers/enumerate/enumerate.hpp"
#include "lexer/lexers/itemize/itemize.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // Lexer.
    // This class is used as an aggregate of all the sub-lexers.
    class Lexer : public lexers::AbstractLexer
    {
    public:
        // The constructor saves a reference to the State object, which is used to store
        // the current state of the parser.
        //
        // * mark_sideways::State state - The state object.
        Lexer(mark_sideways::State *state);

        // The class destructor.
        virtual ~Lexer();

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new string with the lexed tokens.
        //
        // * std::string line   - The string to lex.
        // * return std::string - The lexed string.
        std::string lex(std::string line);

    private:
        // ====================
        // | Private methods. |
        // ====================

        // Lex a line from the head of the file.
        //
        // * std::string line   - The line to lex.
        // * return std::string - The lexed line.
        std::string lex_head(std::string line);

        // Lex a line from the body of the file.
        //
        // * std::string line   - The line to lex.
        // * return std::string - The lexed line.
        std::string lex_body(std::string line);

        // ===========================
        // | The various sub-lexers. |
        // ===========================

        // 2. The enumerate lexer.
        //    \d. List item.
        mark_sideways::lexers::Enumerate *enumerate;

        // 3. The itemize lexer.
        //    * List item.
        mark_sideways::lexers::Itemize *itemize;
    };
}

#endif