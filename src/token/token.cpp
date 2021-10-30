// //token
// v. 0.4.0
//
// Author: Cayden Lund
//   Date: 10/30/2021
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
    // The one-argument constructor saves the type of the token.
    //
    // * const token_type &type - The type of the token.
    Token::Token(const token_type &type) : type(type), value()
    {
    }

    // The constructor saves the type and value of the token.
    //
    // * const token_type &type        - The type of the token.
    // * const std::string_view &value - The value of the token.
    Token::Token(const token_type &type, const std::string &value) : type(type), value()
    {
        this->value << value;
    }

    // The copy constructor saves the type and value of the token.
    //
    // * const Token &other - The token to copy.
    Token::Token(const Token &other) : type(other.type), value()
    {
        this->value << other.value.str();
    }

    // The get_type method returns the type of the token.
    //
    // * return token_type - The type of the token.
    token_type Token::get_type() const
    {
        return this->type;
    }

    // The get_value method returns the value of the token.
    //
    // * return std::string - The value of the token.
    std::string Token::get_value() const
    {
        return this->value.str();
    }

    // Override the = operator to allow for assignment of a token.
    //
    // * const Token &other - The token to assign.
    void Token::operator=(const Token &other)
    {
        this->type = other.type;
        this->value << other.value.str();
    }

    // Override the == operator to compare two tokens.
    //
    // * Token other - The token to compare to.
    // * return bool  - Whether the two tokens are equal.
    bool Token::operator==(const Token &other) const
    {
        return this->type == other.type && this->value.str() == other.value.str();
    }

    // Override the != operator to compare two tokens.
    //
    // * Token other - The token to compare to.
    // * return bool  - Whether the two tokens are not equal.
    bool Token::operator!=(const Token &other) const
    {
        return !(*this == other);
    }

    // The get_token_type method returns the string representation of the token type.
    //
    // * const token_type &type    - The type of the token.
    // * return std::string                              - The string representation of the token type.
    std::string Token::get_token_type(const token_type &type)
    {
        switch (type)
        {
        case token_type::SPACE:
            return "Space";
        case token_type::DOLLAR:
            return "Dollar";
        case token_type::COLON:
            return "Colon";
        case token_type::HASH:
            return "Hash";
        case token_type::STAR:
            return "Asterisk";
        case token_type::DASH:
            return "Dash";
        case token_type::EQUALS:
            return "Equals";
        case token_type::ESCAPE:
            return "Backslash";
        case token_type::NUMBER:
            return "Number";
        case token_type::TERMINAL:
            return "Literal";
        default:
            return "Unknown";
        }
    }

    // The tokens_equal method returns whether two vectors of tokens are equal.
    //
    // * const std::vector<Token> &tokens1 - The first vector of tokens.
    // * const std::vector<Token> &tokens2 - The second vector of tokens.
    // * return bool                       - Whether the two vectors of tokens are equal.
    bool Token::tokens_equal(const std::vector<Token> &tokens1, const std::vector<Token> &tokens2)
    {
        if (tokens1.size() != tokens2.size())
        {
            return false;
        }

        const unsigned int size = tokens1.size();

        for (unsigned int i = 0; i < size; i++)
        {
            if (tokens1[i] != tokens2[i])
                return false;
        }

        return true;
    }

    // The print_tokens method returns the string representation of a vector of tokens.
    //
    // * const std::vector<Token> & tokens - The vector of tokens to print.
    // * return std::string                - The string representation of the vector of tokens.
    std::string Token::print_tokens(const std::vector<Token> &tokens)
    {
        std::stringstream ss;
        ss << "Tokens (" << tokens.size() << "):" << std::endl;
        for (const Token token : tokens)
        {
            ss << Token::get_token_type(token.get_type()) << ": \"" << token.get_value() << "\"" << std::endl;
        }
        return ss.str();
    }
}
