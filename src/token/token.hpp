// //token
//
// Author: Cayden Lund
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the Token class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#ifndef TOKEN_HPP
#define TOKEN_HPP

// System imports.
#include <string>
#include <sstream>

namespace sparkdown
{
    // An enumeration of the possible token types.
    enum token_type
    {
        // Tokens that are used in the lexer and the parser.
        SPACE,    // A space.             [ \t]+
        DOLLAR,   // A dollar sign.       $
        COLON,    // A colon.             :
        LBRAC,    // A left bracket.      [
        RBRAC,    // A right bracket.     ]
        HASH,     // A hash.              #
        STAR,     // An asterisk.         *
        DASH,     // A dash.              [-]+
        EQUALS,   // An equals sign.      [=]+
        LT,       // A less-than sign.    <
        GT,       // A greater-than sign. >
        PIPE,     // A vertical bar.      |
        TICK,     // A backtick.          [`]+
        ESCAPE,   // A backslash.
        NUMBER,   // A numeral.           [0-9]+
        TERMINAL, // A string that should be passed through as-is.

        // The following tokens are not used by the lexer;
        // rather, they have special syntactic meaning and are created by the parser.
        HEADER,      // A header command.
        SECTION,     // A section headline.
        ARROW,       // An arrow.
        BULLET,      // A bullet point.
        NUMBERED,    // A numbered list item.
        BOLD,        // Bold text.
        ITALIC,      // Italic text.
        INLINE_MATH, // An inline math block.
        INLINE_VERB  // An inline verbatim block.
    };

    // Token
    //    This class is the token class, used to store the type and value of a token.
    //    The Lexer class will create a list of tokens from a string.
    //    These tokens are then used by the Parser class to parse the input line into LaTeX code.
    class Token
    {
    public:
        // constructor
        //    The one-argument constructor saves the type of the token.
        //
        // Parameters:
        //    const token_type &type - The type of the token.
        Token(const token_type &type);

        // constructor
        //    The two-argument constructor saves the type and value of the token.
        //
        // Parameters:
        //    const token_type &type        - The type of the token.
        //    const std::string_view &value - The value of the token.
        //       OR
        //    const char &value             - The value of the token.
        Token(const token_type &type, const std::string &value);
        Token(const token_type &type, const char &value);

        // constructor
        //    The copy constructor saves the type and value of the token.
        //
        // Parameters:
        //    const Token &other - The token to copy.
        Token(const Token &other);

        // merge
        //    Merges two tokens together.
        //
        // Parameters:
        //    const Token &other - The token to merge with.
        void merge(const Token &other);

        // get_type
        //    Returns the type of the token.
        //
        // Returns:
        //    token_type - The type of the token.
        token_type get_type() const;

        // get_value
        //    Returns the string value of the token.
        //
        // Returns:
        //    std::string - The value of the token.
        std::string get_value() const;

        // = operator
        //    Allow for assignment of tokens.
        //
        // Parameters:
        //    const Token &other - The token to assign.
        void operator=(const Token &other);

        // == operator
        //    Compare two tokens for equality.
        //
        // Parameters:
        //    const Token &other - The token with which to compare.
        //
        // Returns:
        //    bool - True when the tokens are equal.
        bool operator==(const Token &other) const;

        // != operator
        //    Compare two tokens for inequality.
        //
        // Parameters:
        //    const Token &other - The token with which to compare.
        //
        // Returns:
        //    bool - True when the tokens are not equal.
        bool operator!=(const Token &other) const;

        // ===========================
        // || Public static methods ||
        // ===========================

        // get_token_type
        //    Returns the string representation of the token type.
        //
        // Parameters:
        //    const token_type &type - The type of the token.
        //
        // Returns:
        //    std::string - The string representation of the token type.
        static std::string get_token_type(const token_type &type);

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
        static bool tokens_equal(const std::vector<Token> &tokens1, const std::vector<Token> &tokens2);

        // print_tokens
        //    Returns a string representation of a vector of tokens.
        //
        // Parameters:
        //    const std::vector<Token> &tokens - The vector of tokens.
        //
        // Returns:
        //    std::string - The string representation of the vector of tokens.
        static std::string print_tokens(const std::vector<Token> &tokens);

    protected:
        // The type of the token.
        token_type type;

        // The value of the token.
        std::stringstream value;
    };
}

#endif