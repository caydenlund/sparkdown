// //token
//
// Author: Cayden Lund
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
#include <vector>
#include <sstream>
#include <iostream>

// The header for the Token class.
#include "token.hpp"

namespace sparkdown
{
    // constructor
    //    The one-argument constructor saves the type of the token.
    //
    // Parameters:
    //    const token_type &type - The type of the token.
    Token::Token(const token_type &type) : type(type), value() {}

    // constructor
    //    The two-argument constructor saves the type and value of the token.
    //
    // Parameters:
    //    const token_type &type        - The type of the token.
    //    const std::string_view &value - The value of the token.
    //       OR
    //    const char &value             - The value of the token.
    Token::Token(const token_type &type, const std::string &value) : type(type), value()
    {
        this->value << value;
    }
    Token::Token(const token_type &type, const char &value) : type(type), value()
    {
        this->value << value;
    }

    // constructor
    //    The copy constructor saves the type and value of the token.
    //
    // Parameters:
    //    const Token &other - The token to copy.
    Token::Token(const Token &other) : type(other.type), value()
    {
        this->value << other.value.str();
    }

    // merge
    //    Merges two tokens together.
    //
    // Parameters:
    //    const Token &other - The token to merge with.
    void Token::merge(const Token &other)
    {
        this->value << other.value.str();
    }

    // get_type
    //    Returns the type of the token.
    //
    // Returns:
    //    token_type - The type of the token.
    token_type Token::get_type() const
    {
        return this->type;
    }

    // get_value
    //    Returns the string value of the token.
    //
    // Returns:
    //    std::string - The value of the token.
    std::string Token::get_value() const
    {
        return this->value.str();
    }

    // = operator
    //    Allow for assignment of tokens.
    //
    // Parameters:
    //    const Token &other - The token to assign.
    void Token::operator=(const Token &other)
    {
        this->type = other.type;
        this->value << other.value.str();
    }

    // == operator
    //    Compare two tokens for equality.
    //
    // Parameters:
    //    const Token &other - The token with which to compare.
    //
    // Returns:
    //    bool - True when the tokens are equal.
    bool Token::operator==(const Token &other) const
    {
        return this->type == other.type && this->value.str() == other.value.str();
    }

    // != operator
    //    Compare two tokens for inequality.
    //
    // Parameters:
    //    const Token &other - The token with which to compare.
    //
    // Returns:
    //    bool - True when the tokens are not equal.
    bool Token::operator!=(const Token &other) const
    {
        return !(*this == other);
    }

    // get_token_type
    //    Returns the string representation of the token type.
    //
    // Parameters:
    //    const token_type &type - The type of the token.
    //
    // Returns:
    //    std::string - The string representation of the token type.
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

    // tokens_equal
    //    Returns true when two vectors of tokens are equal.
    //    Used heavily in unit tests.
    //
    // Parameters:
    //    const std::vector<Token> &tokens1 - The first vector of tokens.
    //    const std::vector<Token> &tokens2 - The second vector of tokens.
    //
    // Returns:
    //    bool - True when the two vectors of tokens are equal.
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

    // print_tokens
    //    Returns a string representation of a vector of tokens.
    //
    // Parameters:
    //    const std::vector<Token> &tokens - The vector of tokens.
    //
    // Returns:
    //    std::string - The string representation of the vector of tokens.
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
