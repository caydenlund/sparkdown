// src/lexer/lexers/arrow/arrow.cpp
// v. 0.1.2
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the arrow lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// The arrow header file.
#include "arrow.hpp"

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
        sparkdown::lexers::Arrow::Arrow(sparkdown::State *state) : AbstractLexer(state)
        {
            // The regex for the lexer.
            this->match_regex = std::regex("(<?[-=]+>|<[-=]+)");
            this->escape_regex = std::regex("\\\\(<?[-=]+>|<[-=]+)");
        }

        // The class destructor.
        sparkdown::lexers::Arrow::~Arrow()
        {
            // Nothing to do here.
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line                  - The string to lex.
        // * return std::vector<sparkdown::Token> - The vector of tokens.
        std::vector<sparkdown::Token> sparkdown::lexers::Arrow::lex(const std::string &line)
        {
            // The vector of tokens to return.
            std::vector<sparkdown::Token> tokens;

            // First, determine whether we are in a block of verbatim text.
            if (this->state->is_verbatim())
            {
                // If so, add the line back as an unlexed token.
                tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, line));
            }
            else
            {
                // If we are not in verbatim mode, then we can test whether the line contains an arrow
                // or an escape sequence.
                std::smatch match;
                if (std::regex_search(line, match, this->escape_regex))
                {
                    // If the line contains an escaped arrow, then we add it back as a text literal.
                    std::string escaped_arrow = match.str().substr(1);

                    int index = match.position();

                    std::string before = line.substr(0, index);
                    std::string after = line.substr(index + escaped_arrow.length() + 1);

                    std::vector<sparkdown::Token> before_tokens = this->lex(before);
                    std::vector<sparkdown::Token> after_tokens = this->lex(after);

                    if (before_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), before_tokens.begin(), before_tokens.end());
                    }
                    tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::TEXT_CONTENT, escaped_arrow));
                    if (after_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), after_tokens.begin(), after_tokens.end());
                    }
                    return tokens;
                }
                else if (std::regex_search(line, match, this->match_regex))
                {
                    // If the line contains an arrow, then we need to lex it.
                    std::string arrow = match.str();

                    int index = match.position();

                    std::string before = line.substr(0, index);
                    std::string after = line.substr(index + arrow.length());

                    std::vector<sparkdown::Token> before_tokens = this->lex(before);
                    std::vector<sparkdown::Token> after_tokens = this->lex(after);

                    if (before_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), before_tokens.begin(), before_tokens.end());
                    }
                    tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::ARROW, arrow));
                    if (after_tokens.size() > 0)
                    {
                        tokens.insert(tokens.end(), after_tokens.begin(), after_tokens.end());
                    }
                }
                else if (!line.empty())
                {
                    // If the line does not contain an arrow, then we add it back as an unlexed token.
                    tokens.push_back(sparkdown::Token(sparkdown::Token::token_type::UNLEXED, line));
                }
            }
            return tokens;
        }
    }
}
