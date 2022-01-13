// //lexer
//
// Author: Cayden Lund
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

namespace sparkdown
{
    // merge_next
    //    If the two given tokens are both of the same type and that type is in the following list,
    //    then merge the two tokens into one.
    //
    //    Mergeable types (token_type):
    //       * TERMINAL
    //       * SPACE
    //       * EQUALS
    //       * TICK
    //       * NUMBER
    //
    // Parameters:
    //    Token &new_token        - The token to be merged with the next token.
    //    const Token &next_token - The next token to be merged with the new token.
    //
    // Returns:
    //    bool - True when the two tokens are merged.
    bool merge_next(Token &new_token, const Token &next_token)
    {
        // If the two tokens are both of the same type and that type is in the following list,
        // then merge the two tokens into one.
        if (new_token.get_type() == next_token.get_type() &&
            (new_token.get_type() == token_type::TERMINAL ||
             new_token.get_type() == token_type::SPACE ||
             new_token.get_type() == token_type::EQUALS ||
             new_token.get_type() == token_type::TICK ||
             new_token.get_type() == token_type::NUMBER))
        {
            // Merge the two tokens into one.
            new_token.merge(next_token);
            return true;
        }
        return false;
    }

    // consolidate
    //    Consolidates a vector of tokens into fewer, parsable tokens.
    //
    // Parameters:
    //    const std::vector<Token> &tokens - The vector of tokens to consolidate.
    //
    // Returns:
    //    std::vector<Token> - The consolidated vector of tokens.
    std::vector<Token> consolidate(const std::vector<Token> &tokens)
    {
        std::vector<Token> consolidated_tokens;
        size_t size = tokens.size();
        for (size_t i = 0; i < size; i++)
        {
            // If the tokens can't be merged, push it to the back.
            if (consolidated_tokens.size() == 0 || !merge_next(consolidated_tokens.back(), tokens[i]))
                consolidated_tokens.push_back(tokens[i]);
        }
        return consolidated_tokens;
    }

    // lex
    //    Used to lex a line for parsing.
    //
    // Parameters:
    //    const std::string &line  - The line to lex.
    //
    // Returns:
    //    std::vector<Token> - A vector of tokens.
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

        tokens = consolidate(tokens);

        return tokens;
    }
}
