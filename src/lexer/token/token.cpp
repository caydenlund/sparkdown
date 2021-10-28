// //token
// v. 0.2.2
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the Token class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <sstream>
#include <iostream>

// The header for the Token class.
#include "token.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The constructor saves the type and value of the token.
    //
    // * token_type type   - The type of the token.
    // * std::string value - The value of the token.
    sparkdown::Token::Token(sparkdown::Token::token_type type, std::string value)
    {
        this->type = type;
        this->value = value;
    }

    // The get_type method returns the type of the token.
    //
    // * return token_type - The type of the token.
    sparkdown::Token::token_type sparkdown::Token::get_type()
    {
        return this->type;
    }

    // The get_value method returns the value of the token.
    //
    // * return std::string - The value of the token.
    std::string sparkdown::Token::get_value()
    {
        return this->value;
    }

    // Override the == operator to compare two tokens.
    //
    // * Token other - The token to compare to.
    // * return bool  - Whether the two tokens are equal.
    bool sparkdown::Token::operator==(const Token &other)
    {
        return this->type == other.type && this->value == other.value;
    }

    // Override the != operator to compare two tokens.
    //
    // * Token other - The token to compare to.
    // * return bool  - Whether the two tokens are not equal.
    bool sparkdown::Token::operator!=(const Token &other)
    {
        return !(*this == other);
    }

    // The get_token_type method returns the string representation of the token type.
    //
    // * const sparkdown::Token::token_type &type    - The type of the token.
    // * return std::string                              - The string representation of the token type.
    std::string sparkdown::Token::get_token_type(const sparkdown::Token::token_type &type)
    {
        switch (type)
        {
        case sparkdown::Token::token_type::UNLEXED:
            return "Unlexed";
        case sparkdown::Token::token_type::HEADER:
            return "Header";
        case sparkdown::Token::token_type::INDENTATION:
            return "Indentation";
        case sparkdown::Token::token_type::TEXT_CONTENT:
            return "Text Content";
        case sparkdown::Token::token_type::VERB_BLOCK:
            return "Verb Block";
        case sparkdown::Token::token_type::INLINE_VERB:
            return "Inline Verb";
        case sparkdown::Token::token_type::MATH_BLOCK:
            return "Math Block";
        case sparkdown::Token::token_type::INLINE_MATH:
            return "Inline Math";
        case sparkdown::Token::token_type::SECTION:
            return "Section";
        case sparkdown::Token::token_type::ARROW:
            return "Arrow";
        case sparkdown::Token::token_type::BULLET:
            return "Bullet";
        case sparkdown::Token::token_type::ENUMERATE:
            return "Enumerate";
        case sparkdown::Token::token_type::BOLD:
            return "Bold";
        case sparkdown::Token::token_type::ITALIC:
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
    bool sparkdown::Token::tokens_equal(const std::vector<Token> &tokens1, const std::vector<Token> &tokens2)
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
    std::string sparkdown::Token::print_tokens(const std::vector<Token> &tokens)
    {
        std::stringstream ss;
        ss << "Tokens (" << tokens.size() << "):" << std::endl;
        for (Token token : tokens)
        {
            ss << sparkdown::Token::get_token_type(token.get_type()) << ": \"" << token.get_value() << "\"" << std::endl;
        }
        return ss.str();
    }
}
