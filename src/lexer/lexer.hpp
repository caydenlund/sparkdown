// //lexer
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the header of the lex() method.
// This method is used to lex a line for parsing.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#ifndef LEXER_HPP
#define LEXER_HPP

// System imports.
#include <string>
#include <vector>

// We use the Token class to build a vector of tokens.
#include "token/token.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The lex() method is used to lex a line for parsing.
    //
    // * const std::string &line  - The line to lex.
    // * return std::vector<Token> - A vector of tokens.
    std::vector<Token> lex(const std::string &line);
}

#endif