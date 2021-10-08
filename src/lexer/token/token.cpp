// src/token/token.cpp
// v. 0.1.2
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the Token class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>

// The header for the Token class.
#include "token.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // The constructor saves the type and value of the token.
    //
    // * token_type type   - The type of the token.
    // * std::string value - The value of the token.
    mark_sideways::Token::Token(mark_sideways::Token::token_type type, std::string value)
    {
        this->type = type;
        this->value = value;
    }

    // The get_type method returns the type of the token.
    //
    // * return token_type - The type of the token.
    mark_sideways::Token::token_type mark_sideways::Token::get_type()
    {
        return this->type;
    }

    // The get_value method returns the value of the token.
    //
    // * return std::string - The value of the token.
    std::string mark_sideways::Token::get_value()
    {
        return this->value;
    }

    // Override the == operator to compare two tokens.
    //
    // * Token other - The token to compare to.
    // * return bool  - Whether the two tokens are equal.
    bool mark_sideways::Token::operator==(const Token &other)
    {
        return this->type == other.type && this->value == other.value;
    }

    // Override the != operator to compare two tokens.
    //
    // * Token other - The token to compare to.
    // * return bool  - Whether the two tokens are not equal.
    bool mark_sideways::Token::operator!=(const Token &other)
    {
        return !(*this == other);
    }
}
