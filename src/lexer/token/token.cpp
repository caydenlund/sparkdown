// src/token/token.cpp
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
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

    // The get_token_type method returns the string representation of the token type.
    //
    // * const mark_sideways::Token::token_type &type    - The type of the token.
    // * return std::string                              - The string representation of the token type.
    std::string mark_sideways::Token::get_token_type(const mark_sideways::Token::token_type &type)
    {
        switch (type)
        {
        case mark_sideways::Token::token_type::UNLEXED:
            return "Unlexed";
        case mark_sideways::Token::token_type::HEADER:
            return "Header";
        case mark_sideways::Token::token_type::INDENTATION:
            return "Indentation";
        case mark_sideways::Token::token_type::TEXT_CONTENT:
            return "Text Content";
        case mark_sideways::Token::token_type::VERB_BLOCK:
            return "Verb Block";
        case mark_sideways::Token::token_type::INLINE_VERB:
            return "Inline Verb";
        case mark_sideways::Token::token_type::MATH_BLOCK:
            return "Math Block";
        case mark_sideways::Token::token_type::INLINE_MATH:
            return "Inline Math";
        case mark_sideways::Token::token_type::SECTION:
            return "Section";
        case mark_sideways::Token::token_type::ARROW:
            return "Arrow";
        case mark_sideways::Token::token_type::BULLET:
            return "Bullet";
        case mark_sideways::Token::token_type::ENUMERATE:
            return "Enumerate";
        case mark_sideways::Token::token_type::BOLD:
            return "Bold";
        case mark_sideways::Token::token_type::ITALIC:
            return "Italic";
        default:
            return "Unknown";
        }
    }

    // The tokens_equal method returns whether two vectors of tokens are equal.
    //
    // * const std::vector<Token> &tokens1 - The first vector of tokens.
    // * const std::vector<Token> &tokens2 - The second vector of tokens.
    // * return bool                       - Whether the two vectors of tokens are equal.
    bool mark_sideways::Token::tokens_equal(const std::vector<Token> &tokens1, const std::vector<Token> &tokens2)
    {
        if (tokens1.size() != tokens2.size())
        {
            return false;
        }

        const unsigned int size = tokens1.size();

        for (unsigned int i = 0; i < size; i++)
        {
            if ((Token)tokens1[i] != (Token)tokens2[i])
                return false;
        }

        return true;
    }

    // The print_tokens method returns the string representation of a vector of tokens.
    //
    // * const std::vector<Token> & tokens - The vector of tokens to print.
    // * return std::string                - The string representation of the vector of tokens.
    std::string mark_sideways::Token::print_tokens(const std::vector<Token> &tokens)
    {
        std::stringstream ss;
        ss << "Tokens (" << tokens.size() << "):" << std::endl;
        for (Token token : tokens)
        {
            ss << mark_sideways::Token::get_token_type(token.get_type()) << ": \"" << token.get_value() << "\"" << std::endl;
        }
        return ss.str();
    }
}
