// src/token/token.hpp
// v. 0.2.1
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the Token class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef TOKEN_HPP
#define TOKEN_HPP

// System imports.
#include <string>
#include <regex>

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // Token.
    // This class is the token class, instantiated by the various lexers.
    // These tokens are then used by the Parser class to parse the input line into LaTeX code.
    // Tokens are immutable; once instantiated, their values are read-only.
    class Token
    {
    public:
        // An enumeration of the possible token types.
        enum token_type
        {
            UNLEXED,      //    Content that we have not yet lexed.
                          //  ==============================
            HEADER,       //    A meta-command at the head of the document.
                          //  ==============================
            INDENTATION,  //    Indentation.
                          //  ==============================
            TEXT_CONTENT, //    Literal text content.
                          //  ==============================
            VERB_BLOCK,   //    ```
                          //    Block of verbatim text.
                          //    ```
                          //  ==============================
            INLINE_VERB,  //    |Inline verbatim text.|
                          //  ==============================
            MATH_BLOCK,   //    $$
                          //    y = mx + b
                          //    $$
                          //    \[
                          //    y = mx + b
                          //    \]
                          //  ==============================
            INLINE_MATH,  //    $y = mx + b$
                          //  ==============================
            SECTION,      //    # A headline.
                          //    ## A subheadline.
                          //  ==============================
            ARROW,        //    -> Rightarrow.
                          //    => Rightarrow.
                          //    --> Rightarrow.
                          //    ==> Rightarrow.
                          //    <- Leftarrow.
                          //    <= Leftarrow.
                          //    <-- Leftarrow.
                          //    <== Leftarrow.
                          //    <-> Leftrightarrow.
                          //    <=> Leftrightarrow.
                          //    <--> Leftrightarrow.
                          //    <==> Leftrightarrow.
                          //  ==============================
            BULLET,       //    * A bullet point.
                          //    - A bullet point.
                          //  ==============================
            ENUMERATE,    //    1. Item of a numbered list.
                          //  ==============================
            BOLD,         //    **Inline bold text.**
                          //  ==============================
            ITALIC        //    *Inline italic text.*
        };

        // The constructor saves the type and value of the token.
        //
        // * token_type type   - The type of the token.
        // * std::string value - The value of the token.
        Token(token_type type, std::string value);

        // The get_type method returns the type of the token.
        //
        // * return token_type - The type of the token.
        token_type get_type();

        // The get_value method returns the value of the token.
        //
        // * return std::string - The value of the token.
        std::string get_value();

        // Override the == operator to compare two tokens.
        //
        // * Token other - The token to compare to.
        // * return bool  - Whether the two tokens are equal.
        bool operator==(const Token &other);

        // Override the != operator to compare two tokens.
        //
        // * Token other - The token to compare to.
        // * return bool  - Whether the two tokens are not equal.
        bool operator!=(const Token &other);

        // ==========================
        // | Public static methods. |
        // ==========================

        // The get_token_type method returns the string representation of the token type.
        //
        // * const token_type &type    - The type of the token.
        // * return std::string - The string representation of the token type.
        static std::string get_token_type(const token_type &type);

        // The tokens_equal method returns whether two vectors of tokens are equal.
        //
        // * const std::vector<Token> &tokens1 - The first vector of tokens.
        // * const std::vector<Token> &tokens2 - The second vector of tokens.
        // * return bool                       - Whether the two vectors of tokens are equal.
        static bool tokens_equal(const std::vector<Token> &tokens1, const std::vector<Token> &tokens2);

        // The print_tokens method returns the string representation of a vector of tokens.
        //
        // * const std::vector<Token> &tokens - The vector of tokens to print.
        // * return std::string               - The string representation of the vector of tokens.
        static std::string print_tokens(const std::vector<Token> &tokens);

    protected:
        // The type of the token.
        token_type type;

        // The value of the token.
        std::string value;
    };
}

#endif