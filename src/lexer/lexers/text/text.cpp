// //lexer/lexers/text
// v. 0.1.1
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the text lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <regex>

// The text header file.
#include "text.hpp"

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
        // State *state - The state object.
        lexers::Text::Text(State *state) : AbstractLexer(state)
        {
            // The regular expression for characters to erase.
            this->erase_regex = std::regex("\\n");
        }

        // The class destructor.
        lexers::Text::~Text()
        {
            // Nothing to do here.
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * const std::string &line   - The string to lex.
        // * return std::vector<Token> - The vector of tokens.
        std::vector<Token> lexers::Text::lex(const std::string &line)
        {
            // The vector of tokens to return.
            std::vector<Token> tokens;

            std::string new_string = std::regex_replace(line, this->erase_regex, "");

            if (!new_string.empty())
            {
                tokens.push_back(Token(Token::token_type::TEXT_CONTENT, std::regex_replace(line, this->erase_regex, "")));
            }

            return tokens;
        }
    }
}
