// src/lexer/lexer.cpp
// v. 0.2.4
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
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
#include "lexer/lexers/bold/bold.hpp"
#include "lexer/lexers/italic/italic.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The class constructor.
    //
    // * sparkdown::State *state - The State object to use for keeping track of the state of the parser.
    sparkdown::Lexer::Lexer(sparkdown::State *state) : sparkdown::lexers::AbstractLexer(state)
    {
        // The various sub-lexers.
        this->header = new sparkdown::lexers::Header(this->state);
        this->section = new sparkdown::lexers::Section(this->state);
        this->verbatim = new sparkdown::lexers::Verbatim(this->state);
        this->arrow = new sparkdown::lexers::Arrow(this->state);
        this->enumerate = new sparkdown::lexers::Enumerate(this->state);
        this->itemize = new sparkdown::lexers::Itemize(this->state);
        this->bold = new sparkdown::lexers::Bold(this->state);
        this->italic = new sparkdown::lexers::Italic(this->state);
    }

    // The class destructor.
    sparkdown::Lexer::~Lexer()
    {
        delete this->header;
        delete this->section;
        delete this->verbatim;
        delete this->arrow;
        delete this->enumerate;
        delete this->itemize;
        delete this->bold;
        delete this->italic;
    }

    // lex() is used to lex a single input line.
    // This method takes in a string and returns a new string with the lexed tokens.
    //
    // * const std::string &line - The line to lex.
    // * return std::string      - The lexed line.
    std::vector<sparkdown::Token> sparkdown::Lexer::lex(const std::string &line)
    {
        std::vector<sparkdown::Token> tokens;
        tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, line));
        this->lex(tokens);
        return tokens;
    }

    // A recursive helper method to lex a single line.
    //
    // * std::vector<sparkdown::Token> &tokens - The vector of tokens.
    // * return std::vector<sparkdown::Token>  - The new vector of tokens.
    std::vector<sparkdown::Token> sparkdown::Lexer::lex(std::vector<sparkdown::Token> &tokens)
    {
        std::vector<sparkdown::Token> new_tokens;
        if (tokens.size() == 0)
        {
            return tokens;
        }
        for (int i = 0; i < (int)tokens.size(); i++)
        {
            new_tokens.clear();
            if (tokens[i].get_type() == sparkdown::Token::token_type::UNLEXED)
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
                    if (tokens[0].get_type() == sparkdown::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->section->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }

                    // If the first token is still UNLEXED, we pass it through the verbatim lexer.
                    if (tokens[0].get_type() == sparkdown::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->verbatim->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }

                    // If the first token is still UNLEXED, we pass it through the itemize lexer.
                    if (tokens[0].get_type() == sparkdown::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->itemize->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }

                    // If the first token is still UNLEXED, we pass it through the enumerate lexer.
                    if (tokens[0].get_type() == sparkdown::Token::token_type::UNLEXED)
                    {
                        new_tokens = this->enumerate->lex(tokens[0].get_value());
                        tokens.erase(tokens.begin());
                        tokens.insert(tokens.begin(), new_tokens.begin(), new_tokens.end());
                    }
                }

                // If this token is still UNLEXED, we pass it through the arrow lexer.
                if (tokens[i].get_type() == sparkdown::Token::token_type::UNLEXED)
                {
                    new_tokens = this->arrow->lex(tokens[i].get_value());
                    tokens.erase(tokens.begin() + i);
                    tokens.insert(tokens.begin() + i, new_tokens.begin(), new_tokens.end());
                }

                // If this token is still UNLEXED, we pass it through the bold lexer.
                if (tokens[i].get_type() == sparkdown::Token::token_type::UNLEXED)
                {
                    new_tokens = this->bold->lex(tokens[i].get_value());
                    tokens.erase(tokens.begin() + i);
                    tokens.insert(tokens.begin() + i, new_tokens.begin(), new_tokens.end());
                }

                // If this token is still UNLEXED, we pass it through the italic lexer.
                if (tokens[i].get_type() == sparkdown::Token::token_type::UNLEXED)
                {
                    new_tokens = this->italic->lex(tokens[i].get_value());
                    tokens.erase(tokens.begin() + i);
                    tokens.insert(tokens.begin() + i, new_tokens.begin(), new_tokens.end());
                }
            }
        }
        return tokens;
    }
}
