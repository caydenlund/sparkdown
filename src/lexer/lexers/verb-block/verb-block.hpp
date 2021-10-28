// //lexer/lexers/verb-block
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the verbatim block lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#ifndef VERB_BLOCK_HPP
#define VERB_BLOCK_HPP

// System imports.
#include <string>
#include <regex>
#include <vector>

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// We use the Token class to build a vector of tokens.
#include "lexer/token/token.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The lexers namespace contains all the sub-lexer classes.
    namespace lexers
    {
        // VerbBlock.
        // This class is used to lex blocks of verbatim text.
        class VerbBlock : public AbstractLexer
        {
        public:
            // The constructor saves a reference to the State object, which is used to store
            // the current state of the parser.
            //
            // * State *state - The state object.
            VerbBlock(State *state);

            // The class destructor.
            virtual ~VerbBlock();

            // lex() is used to lex a single input line.
            // This method takes in a string and returns a new vector with the lexed tokens.
            //
            // * const std::string &line   - The string to lex.
            // * return std::vector<Token> - The vector of tokens.
            std::vector<Token> lex(const std::string &line);

        private:
            // The regex used to lex verbatim blocks.
            std::regex match_regex;
        };
    }
}

#endif