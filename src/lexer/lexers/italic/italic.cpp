// src/lexer/lexers/italic/italic.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/16/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the italic lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// The italic header file.
#include "italic.hpp"

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
        mark_sideways::lexers::Italic::Italic(mark_sideways::State *state) : AbstractLexer(state)
        {
            // The regex for the lexer.
            this->match_regex = std::regex("\\*([^]+?)\\*");

            // Matches "\*".
            this->escape_regex = std::regex("\\\\\\*");
        }

        // The class destructor.
        mark_sideways::lexers::Italic::~Italic()
        {
            // Nothing to do here.
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line                  - The string to lex.
        // * return std::vector<mark_sideways::Token> - The vector of tokens.
        std::vector<mark_sideways::Token> mark_sideways::lexers::Italic::lex(const std::string &line)
        {
            // The vector of tokens to return.
            std::vector<mark_sideways::Token> tokens;

            // First, determine whether we are in a block of verbatim text.
            if (this->state->is_verbatim())
            {
                // If so, add the line back as an unlexed token.
                tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, line));
            }
            else if (line.empty())
            {
                // If the line is empty, return an empty vector.
                return tokens;
            }
            else
            {
                // Escape all the escaped italic markers.
                std::smatch match;
                if (std::regex_search(line, match, this->escape_regex))
                {
                    int index = match.position();

                    std::string before = line.substr(0, index);
                    std::string after = line.substr(index + 2);

                    std::vector<mark_sideways::Token> before_tokens = this->lex(before);
                    std::vector<mark_sideways::Token> after_tokens = this->lex(after);

                    if (before_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), before_tokens.begin(), before_tokens.end());
                    }
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, "*"));
                    if (after_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), after_tokens.begin(), after_tokens.end());
                    }
                    return tokens;
                }
                else if (std::regex_search(line, match, this->match_regex))
                {
                    int index = match.position();

                    std::string before = line.substr(0, index);
                    std::string after = line.substr(index + match.length());

                    std::vector<mark_sideways::Token> before_tokens = this->lex(before);
                    std::vector<mark_sideways::Token> after_tokens = this->lex(after);

                    if (before_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), before_tokens.begin(), before_tokens.end());
                    }
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::ITALIC, match.str(1)));
                    if (after_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), after_tokens.begin(), after_tokens.end());
                    }
                    return tokens;
                }
                else
                {
                    // If we didn't match anything, add the line back as an unlexed token.
                    tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, line));
                }
            }
            return tokens;
        }
    }
}
