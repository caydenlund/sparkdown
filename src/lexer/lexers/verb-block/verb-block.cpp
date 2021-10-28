// //lexer/lexers/verb-block
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the verbatim lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <regex>

// The verbatim header file.
#include "verb-block.hpp"

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
        // State state - The state object.
        VerbBlock::VerbBlock(State *state) : AbstractLexer(state)
        {
            // The regex for the lexer.
            this->match_regex = std::regex("^(\\s*)(```)[^\\n]*\\n?");
        }

        // The class destructor.
        VerbBlock::~VerbBlock()
        {
            // Nothing to do here.
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line   - The string to lex.
        // * return std::vector<Token> - The vector of tokens.
        std::vector<Token> VerbBlock::lex(const std::string &line)
        {
            // The vector of tokens to return.
            std::vector<Token> tokens;

            // If we match the regex, we return a new token.
            if (std::regex_match(line, this->match_regex))
            {
                std::string value = "Start";

                if (this->state->is_verbatim())
                    value = "End";

                this->state->toggle_verbatim();

                tokens.push_back(Token(Token::token_type::VERB_BLOCK, value));
            }
            else
            {
                if (this->state->is_verbatim())
                {
                    // If we're inside of a verbatim block, we add the text back as text literal.
                    tokens.push_back(Token(Token::token_type::TEXT_CONTENT, line));
                }
                else
                {
                    // Otherwise, we add the text back as an unlexed token.
                    tokens.push_back(Token(Token::token_type::UNLEXED, line));
                }
            }
            return tokens;
        }
    }
}
