// src/token/token.hpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the headers for the Token class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef ABSTRACT_LEXER_HPP
#define ABSTRACT_LEXER_HPP

// System imports.
#include <string>
#include <regex>

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // Token.
    // This class is the token class, instantiated by the various lexers.
    // These tokens are then used by the Parser class to parse the input line into LaTeX code.
    // Tokens are immutable; once instantiated, their values can only be read.
    class Token
    {
    public:
        // An enumeration of the possible token types.
        enum token_type
        {
            UNLEXED,      //    Content that we have not yet lexed.
                          //  ==============================
            INDENTATION,  //    Indentation.
                          //
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
            HEADLINE,     //    # A headline.
                          //    ## A subheadline.
                          //  ==============================
            R_ARROW,      //    -> Rightarrow.
                          //    => Rightarrow.
                          //    --> Rightarrow.
                          //    ==> Rightarrow.
                          //  ==============================
            L_ARROW,      //    <- Leftarrow.
                          //    <= Leftarrow.
                          //    <-- Leftarrow.
                          //    <== Leftarrow.
                          //  ==============================
            L_R_AROW,     //    <-> Leftrightarrow.
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

    protected:
        // The type of the token.
        token_type type;

        // The value of the token.
        std::string value;
    };
}

#endif