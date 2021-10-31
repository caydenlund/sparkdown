// //lexer
// v. 0.4.0
//
// Author: Cayden Lund
//   Date: 10/30/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the lex() method.
// This method is used to lex a line for parsing.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <vector>

// We use the Token class to build a vector of tokens.
#include "token/token.hpp"

// The header for the lex() method.
#include "lexer.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The lex() method is used to lex a line for parsing.
    //
    // * const std::string &line  - The line to lex.
    // * return std::vector<Token> - A vector of tokens.
    std::vector<Token> lex(const std::string &line)
    {
        // The vector of tokens to return.
        std::vector<Token> tokens;

        // Iterate over the characters in the line.
        for (const char c : line)
        {
            switch (c)
            {
            case ' ':
            case '\t':
                tokens.push_back(Token(token_type::SPACE, c));
                break;
            case '$':
                tokens.push_back(Token(token_type::DOLLAR));
                break;
            case ':':
                tokens.push_back(Token(token_type::COLON));
                break;
            case '[':
                tokens.push_back(Token(token_type::LBRAC));
                break;
            case ']':
                tokens.push_back(Token(token_type::RBRAC));
                break;
            case '#':
                tokens.push_back(Token(token_type::HASH));
                break;
            case '*':
                tokens.push_back(Token(token_type::STAR));
                break;
            case '-':
                tokens.push_back(Token(token_type::DASH));
                break;
            case '=':
                tokens.push_back(Token(token_type::EQUALS));
                break;
            case '<':
                tokens.push_back(Token(token_type::LT));
                break;
            case '>':
                tokens.push_back(Token(token_type::GT));
                break;
            case '|':
                tokens.push_back(Token(token_type::PIPE));
                break;
            case '`':
                tokens.push_back(Token(token_type::TICK));
                break;
            case '\\':
                tokens.push_back(Token(token_type::ESCAPE));
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                tokens.push_back(Token(token_type::NUMBER, c));
                break;
            case '\n':
                // Ignore newlines.
                break;
            default:
                tokens.push_back(Token(token_type::TERMINAL, c));
                break;
            }
        }

        return tokens;
    }
}
