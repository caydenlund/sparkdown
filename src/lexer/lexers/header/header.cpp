// //lexer/lexers/header
// v. 0.1.4
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the header lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <regex>

// The header header file.
#include "header.hpp"

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The lexers namespace contains all the sub-lexer classes.
    namespace lexers
    {
        // The constructor saves a reference to the State object, which is used to store
        // the current state of the parser.
        //
        // sparkdown::State state - The state object.
        sparkdown::lexers::Header::Header(sparkdown::State *state) : AbstractLexer(state)
        {
            this->match_regex = std::regex("^\\$([^:\\s]+):\\s*([^\\n]*)\\n?$");
            this->escape_regex = std::regex("^\\\\(\\$[^:\\s]+:\\s*[^\\n]*\\n?)$");

            this->whitespace_regex = std::regex("^\\s*$");

            // (Separated into groups for readability.)
            this->equals_regex = std::regex("^(\\s*)(=+)(\\s*)(%[^])?(\\n?)$");
        }

        // The class destructor.
        sparkdown::lexers::Header::~Header()
        {
            // Nothing to do here.
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line                  - The string to lex.
        // * return std::vector<sparkdown::Token> - The vector of tokens.
        std::vector<sparkdown::Token> sparkdown::lexers::Header::lex(const std::string &line)
        {
            // The vector of tokens to return.
            std::vector<sparkdown::Token> tokens;

            // First, determine whether we are lexing the head of the document.
            if (this->state->is_head())
            {
                // If we are, we need to check whether the line matches the header regular expression.
                // We can lex the line if it matches the regex.
                if (std::regex_match(line, this->match_regex))
                {
                    std::string value = std::regex_replace(line, this->match_regex, "$1=$2");
                    tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::HEADER, value));
                }
                // If it matches the escape regex, then we are no longer in the head of the document.
                else if (std::regex_match(line, this->escape_regex))
                {
                    std::string value = std::regex_replace(line, this->escape_regex, "$1");
                    tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, value));

                    this->state->end_head();
                }
                // If it matches the equals regex, then we are no longer in the head of the document.
                else if (std::regex_match(line, this->equals_regex))
                {
                    this->state->end_head();
                }
                // If the line is not empty, then we are no longer in the head of the document.
                else if (!std::regex_match(line, this->whitespace_regex))
                {
                    // Add the line back as an unlexed token.
                    tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, line));

                    this->state->end_head();
                }
            }
            else
            {
                // If we are not in the head of the document, then we can just add the line as an unlexed token.
                tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, line));
            }
            return tokens;
        }
    }
}
