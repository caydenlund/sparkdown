// //lexer
// v. 0.3.1
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the Lexer class.
// This class is used to lex a line for parsing.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

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
#include "lexer/lexers/verb-block/verb-block.hpp"
#include "lexer/lexers/arrow/arrow.hpp"
#include "lexer/lexers/enumerate/enumerate.hpp"
#include "lexer/lexers/itemize/itemize.hpp"
#include "lexer/lexers/bold/bold.hpp"
#include "lexer/lexers/italic/italic.hpp"
#include "lexer/lexers/text/text.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // Lexer.
    // This class is used as an aggregate of all the sub-lexers.
    class Lexer : public lexers::AbstractLexer
    {
    public:
        // The constructor saves a reference to the State object, which is used to store
        // the current state of the parser.
        //
        // * State state - The state object.
        Lexer(State *state);

        // The class destructor.
        virtual ~Lexer();

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line                  - The string to lex.
        // * return std::vector<Token> - The vector of tokens.
        std::vector<Token> lex(const std::string &line);

    private:
        // ====================
        // | Private methods. |
        // ====================

        // A helper method to apply a given lexer to the token at the given index.
        //
        // * AbstractLexer *lexer       - The given lexer to apply.
        // * std::vector<Token> &tokens - The vector of tokens.
        // * int index                  - The index at which to apply the lexer.
        void apply_lexer(AbstractLexer *lexer, std::vector<Token> &tokens, int index);

        // ===========================
        // | The various sub-lexers. |
        // ===========================

        // The header lexer.
        //   $item: value
        lexers::Header *header;

        // The section lexer.
        //   # Headline.
        lexers::Section *section;

        // The verbatim block lexer.
        //   ```
        lexers::VerbBlock *verbBlock;

        // The arrow lexer.
        //   ->
        lexers::Arrow *arrow;

        // The enumerate lexer.
        //   \d. List item.
        lexers::Enumerate *enumerate;

        // The itemize lexer.
        //   * List item.
        lexers::Itemize *itemize;

        // The bold lexer.
        //   **Bold text.**
        lexers::Bold *bold;

        // The italic lexer.
        //   *Italic text.*
        lexers::Italic *italic;

        // The text literal lexer.
        //   Text content.
        lexers::Text *text;
    };
}

#endif