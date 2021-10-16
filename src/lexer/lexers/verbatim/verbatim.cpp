// src/lexer/lexers/verbatim/verbatim.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the verbatim lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// The verbatim header file.
#include "verbatim.hpp"

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
        mark_sideways::lexers::Verbatim::Verbatim(mark_sideways::State *state) : AbstractLexer(state)
        {
            // The regex for the lexer.
            this->match_regex = std::regex("^(\\s*)(```)[^\\n]*\\n?");
        }

        // The class destructor.
        mark_sideways::lexers::Verbatim::~Verbatim()
        {
            // Nothing to do here.
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * std::string line                         - The string to lex.
        // * return std::vector<mark_sideways::Token> - The vector of tokens.
        std::vector<mark_sideways::Token> mark_sideways::lexers::Verbatim::lex(std::string line)
        {
            // The vector of tokens to return.
            std::vector<mark_sideways::Token> tokens;

            // If we match the regex, we return a new token.
            if (std::regex_match(line, this->match_regex))
            {
                std::string value = "Start";

                if (this->state->is_verbatim())
                    value = "End";
                
                this->state->toggle_verbatim();
                
                tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::VERB_BLOCK, value));
            }
            else
            {
                if (this->state->is_verbatim())
                {
                    // If we're inside of a verbatim block, we add the text back as text literal.
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, line));
                }
                else
                {
                    // Otherwise, we add the text back as an unlexed token.
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, line));
                }
            }
            return tokens;
        }
    }
}
