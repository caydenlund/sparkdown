// src/lexer/lexer.hpp
// v. 0.2.3
//
// Author: Cayden Lund
//   Date: 10/15/2021
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
#include "state/state.hpp"

// We use the Token class to build a vector of tokens.
#include "lexer/token/token.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

// The various sub-lexers.
#include "lexer/lexers/header/header.hpp"
#include "lexer/lexers/section/section.hpp"
#include "lexer/lexers/verbatim/verbatim.hpp"
#include "lexer/lexers/arrow/arrow.hpp"
#include "lexer/lexers/enumerate/enumerate.hpp"
#include "lexer/lexers/itemize/itemize.hpp"
#include "lexer/lexers/bold/bold.hpp"
#include "lexer/lexers/italic/italic.hpp"

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
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line                  - The string to lex.
        // * return std::vector<mark_sideways::Token> - The vector of tokens.
        std::vector<mark_sideways::Token> lex(const std::string &line);

    private:
        // ====================
        // | Private methods. |
        // ====================

        // A recursive helper method to lex a single line.
        //
        // * std::vector<mark_sideways::Token> &tokens - The vector of tokens.
        // * return std::vector<mark_sideways::Token>  - The new vector of tokens.
        std::vector<mark_sideways::Token> lex(std::vector<mark_sideways::Token> &tokens);

        // ===========================
        // | The various sub-lexers. |
        // ===========================

        // The header lexer.
        //   $item: value
        mark_sideways::lexers::Header *header;

        // The section lexer.
        //   # Headline.
        mark_sideways::lexers::Section *section;

        // The verbatim block lexer.
        //   ```
        mark_sideways::lexers::Verbatim *verbatim;

        // The arrow lexer.
        //   ->
        mark_sideways::lexers::Arrow *arrow;

        // The enumerate lexer.
        //   \d. List item.
        mark_sideways::lexers::Enumerate *enumerate;

        // The itemize lexer.
        //   * List item.
        mark_sideways::lexers::Itemize *itemize;

        // The bold lexer.
        //   **Bold text.**
        mark_sideways::lexers::Bold *bold;

        // The italic lexer.
        //   *Italic text.*
        mark_sideways::lexers::Italic *italic;
    };
}

#endif