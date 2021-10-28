// //lexer
// v. 0.3.0
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the Lexer class.
// This class is used to lex a line for parsing.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

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
#include "lexer/lexers/header/header.hpp"
#include "lexer/lexers/section/section.hpp"
#include "lexer/lexers/verbatim/verbatim.hpp"
#include "lexer/lexers/arrow/arrow.hpp"
#include "lexer/lexers/enumerate/enumerate.hpp"
#include "lexer/lexers/itemize/itemize.hpp"
#include "lexer/lexers/bold/bold.hpp"
#include "lexer/lexers/italic/italic.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The class constructor.
    //
    // * State *state - The State object to use for keeping track of the state of the parser.
    Lexer::Lexer(State *state) : lexers::AbstractLexer(state)
    {
        // The various sub-lexers.
        this->header = new lexers::Header(this->state);
        this->section = new lexers::Section(this->state);
        this->verbatim = new lexers::Verbatim(this->state);
        this->arrow = new lexers::Arrow(this->state);
        this->enumerate = new lexers::Enumerate(this->state);
        this->itemize = new lexers::Itemize(this->state);
        this->bold = new lexers::Bold(this->state);
        this->italic = new lexers::Italic(this->state);
        this->text = new lexers::Text(this->state);
    }

    // The class destructor.
    Lexer::~Lexer()
    {
        delete this->header;
        delete this->section;
        delete this->verbatim;
        delete this->arrow;
        delete this->enumerate;
        delete this->itemize;
        delete this->bold;
        delete this->italic;
        delete this->text;
    }

    // lex() is used to lex a single input line.
    // This method takes in a string and returns a new string with the lexed tokens.
    //
    // * const std::string &line - The line to lex.
    // * return std::string      - The lexed line.
    std::vector<Token> Lexer::lex(const std::string &line)
    {
        std::vector<Token> tokens;
        tokens.push_back(Token(Token::token_type::UNLEXED, line));
        int i = 0;
        while (i < (int)tokens.size())
        {
            if (i == 0)
            {
                // We are currently at the beginning of the line, and nothing has been lexed yet.
                // Some rules apply only to the first token:
                //   * Document header.
                //   * Section header.
                //   * Verbatim.
                //   * Itemize.
                //   * Enumerate.

                // Document header.
                this->apply_lexer(this->header, tokens, i);

                // Section.
                this->apply_lexer(this->section, tokens, i);

                // Verbatim block.
                this->apply_lexer(this->verbatim, tokens, i);

                // Itemize.
                this->apply_lexer(this->itemize, tokens, i);

                // Enumerate.
                this->apply_lexer(this->enumerate, tokens, i);
            }

            // Arrows.
            this->apply_lexer(this->arrow, tokens, i);

            // Bold.
            this->apply_lexer(this->bold, tokens, i);

            // Italics.
            this->apply_lexer(this->italic, tokens, i);

            // Text literal.
            this->apply_lexer(this->text, tokens, i);

            i++;
        }

        return tokens;
    }

    // A helper method to apply a given lexer to the token at the given index.
    //
    // * AbstractLexer *lexer       - The given lexer to apply.
    // * std::vector<Token> &tokens - The vector of tokens.
    // * int index                  - The index at which to apply the lexer.
    void Lexer::apply_lexer(AbstractLexer *lexer, std::vector<Token> &tokens, int index)
    {
        if (tokens[index].get_type() != Token::token_type::UNLEXED)
        {
            return;
        }

        std::vector<Token> new_tokens = lexer->lex(tokens[index].get_value());
        tokens.erase(tokens.begin() + index);

        tokens.insert(tokens.begin() + index, new_tokens.begin(), new_tokens.end());
    }
}
