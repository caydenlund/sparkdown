// src/lexer/lexers/enumerate/enumerate.cpp
// v. 0.3.2
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the enumerate lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// The enumerate header file.
#include "enumerate.hpp"

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // The lexers namespace contains all the sub-lexer classes.
    namespace lexers
    {
        // The constructor saves a reference to the State object, which is used to store
        // the current state of the parser.
        //
        // mark_sideways::State state - The state object.
        mark_sideways::lexers::Enumerate::Enumerate(mark_sideways::State *state) : AbstractLexer(state)
        {
            // The regex for the bullet point lexer.
            this->match_regex = std::regex("^(\\s*)\\d+\\.\\s+([^]*)$");
            this->escape_regex = std::regex("^\\s*\\\\(\\d+\\.\\s+)([^]*)$");
        }

        // The class destructor.
        mark_sideways::lexers::Enumerate::~Enumerate()
        {
            // Nothing to do here.
        }

        // Returns true when a given line is a bullet point.
        //
        // * const std::string &line - The line to check.
        // * return bool      - True if the line is a bullet point.
        bool mark_sideways::lexers::Enumerate::is_enumerate(const std::string &line)
        {
            // To be a bullet point, the state must *not* be in the verbatim state and *not* be in the math state,
            // and the line must match the regular expression.
            return (!this->state->is_verbatim() && !this->state->is_math() && std::regex_match(line, this->match_regex));
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line                  - The string to lex.
        // * return std::vector<mark_sideways::Token> - The vector of tokens.
        std::vector<mark_sideways::Token> mark_sideways::lexers::Enumerate::lex(const std::string &line)
        {
            // The vector of tokens to return.
            std::vector<mark_sideways::Token> tokens;

            // First, determine whether we are in a block of verbatim text or math mode.
            if (this->state->is_verbatim() || this->state->is_math())
            {
                tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, line));
            }
            else
            {
                // If we are not in verbatim or math mode, then we can test whether the line is a bullet point.
                if (std::regex_match(line, this->match_regex))
                {
                    // We can lex the line if it matches the regex.
                    std::string bullet_indentation = std::regex_replace(line, this->match_regex, "$1");
                    int bullet_point_level = (bullet_indentation.length() / 2) + 1;

                    std::string rest = std::regex_replace(line, this->match_regex, "$2");

                    // Add the bullet point token.
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ENUMERATE, std::to_string(bullet_point_level)));

                    // Add the rest as an unlexed token.
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, rest));
                }
                else if (std::regex_match(line, this->escape_regex))
                {
                    // Otherwise, if the line matches the escape regex, then we add the bullet literal as a text token.
                    std::string bullet_literal = std::regex_replace(line, this->escape_regex, "$1");
                    std::string rest = std::regex_replace(line, this->escape_regex, "$2");

                    // Add the text content token.
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, bullet_literal));

                    // Add the rest as an unlexed token.
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, rest));
                }
            }
            return tokens;
        }
    }
}
