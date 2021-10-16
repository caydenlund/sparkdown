// src/lexer/lexer.cpp
// v. 0.2.2
//
// Author: Cayden Lund
//   Date: 10/15/2021
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
#include "lexer/lexers/header/header.hpp"
#include "lexer/lexers/section/section.hpp"
#include "lexer/lexers/verbatim/verbatim.hpp"
#include "lexer/lexers/arrow/arrow.hpp"
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
        // The various sub-lexers.
        this->header = new mark_sideways::lexers::Header(this->state);
        this->section = new mark_sideways::lexers::Section(this->state);
        this->verbatim = new mark_sideways::lexers::Verbatim(this->state);
        this->arrow = new mark_sideways::lexers::Arrow(this->state);
        this->enumerate = new mark_sideways::lexers::Enumerate(this->state);
        this->itemize = new mark_sideways::lexers::Itemize(this->state);
    }

    // The class destructor.
    mark_sideways::Lexer::~Lexer()
    {
        delete this->header;
        delete this->section;
        delete this->verbatim;
        delete this->arrow;
        delete this->enumerate;
        delete this->itemize;
    }

    // lex() is used to lex a single input line.
    // This method takes in a string and returns a new string with the lexed tokens.
    //
    // * const std::string &line - The line to lex.
    // * return std::string      - The lexed line.
    std::vector<mark_sideways::Token> mark_sideways::Lexer::lex(const std::string &line)
    {
        std::vector<mark_sideways::Token> tokens;
        tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, line));
        this->lex(tokens);
        return tokens;
    }

    // A recursive helper method to lex a single line.
    //
    // * std::vector<mark_sideways::Token> &tokens - The vector of tokens.
    // * return std::vector<mark_sideways::Token>  - The new vector of tokens.
    std::vector<mark_sideways::Token> mark_sideways::Lexer::lex(std::vector<mark_sideways::Token> &tokens)
    {
        std::vector<mark_sideways::Token> new_tokens;
        if (tokens.size() == 0)
        {
            return tokens;
        }
        for (int i = 0; i < (int)tokens.size(); i++)
        {
            new_tokens.clear();
            if (tokens[i].get_type() == mark_sideways::Token::token_type::UNLEXED)
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
                    if (this->state->is_head())
                    {
                        new_tokens = this->header->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }

                    // If the first token is still UNLEXED, we pass it through the section lexer.
                    if (tokens[0].get_type() == mark_sideways::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->section->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }

                    // If the first token is still UNLEXED, we pass it through the verbatim lexer.
                    if (tokens[0].get_type() == mark_sideways::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->verbatim->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }

                    // If the first token is still UNLEXED, we pass it through the itemize lexer.
                    if (tokens[0].get_type() == mark_sideways::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->itemize->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }

                    // If the first token is still UNLEXED, we pass it through the enumerate lexer.
                    if (tokens[0].get_type() == mark_sideways::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->enumerate->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }
                }

                // If this token is still UNLEXED, we pass it through the arrow lexer.
                if (tokens[i].get_type() == mark_sideways::Token::token_type::UNLEXED)
                {
                    new_tokens = this->arrow->lex(tokens[i].get_value());
                    tokens.erase(tokens.begin() + i);
                    tokens.insert(tokens.begin() + i, new_tokens.begin(), new_tokens.end());
                }
            }
        }
        return tokens;
    }
}
