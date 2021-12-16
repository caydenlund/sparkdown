// //parser
// v. 0.7.0
//
// Author: Cayden Lund
//   Date: 12/16/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the Parser class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// System imports.
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

// We use the lex() method to lex the input string.
#include "lexer/lexer.hpp"

// The header for the Parser class.
#include "parser.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // The class constructor.
    Parser::Parser() : latex()
    {
    }

    // Parse the given string.
    //
    // * const std::string &input - The string to parse.
    // * return std::string       - The parsed string.
    std::string Parser::parse(const std::string &input)
    {
        std::vector<Token> tokens = lex(input);
        return this->parse(tokens);
    }

    // Parse the given vector of tokens.
    //
    // * std::vector<Token> &tokens - The vector of tokens to parse.
    // * return std::string         - The parsed string.
    std::string Parser::parse(std::vector<Token> &tokens)
    {
        // First, consolidate the tokens.
        Parser::consolidate(tokens);

        size_t size = tokens.size();

        // Our base cases: the size of the vector is 0 or 1.
        if (size == 0)
            return "";
        if (size == 1 && tokens[0].get_type() == token_type::TERMINAL)
            return tokens[0].get_value();

        if (this->in_head)
        {
            // Parse header commands.
            if (size > 3 &&
                tokens[0].get_type() == token_type::DOLLAR &&
                tokens[1].get_type() == token_type::TERMINAL &&
                tokens[2].get_type() == COLON)
            {
                // Replace the first three tokens with a new header token.
                tokens[0] = Token(token_type::HEADER, tokens[1].get_value());
                tokens.erase(tokens.begin() + 1, tokens.begin() + 3);

                // If the second token is now a space, erase it.
                if (tokens[1].get_type() == token_type::SPACE)
                {
                    tokens.erase(tokens.begin() + 1);
                }
            }
            // A nonempty line that doesn't follow the above format signals the end of the header.
            else if (size > 0)
            {
                this->in_head = false;
                // A line of three or more equals characters or hyphens
                // can optionally serve as a divider between the header and the content.
                if (
                    (tokens[0].get_type() == token_type::EQUALS || tokens[0].get_type() == token_type::DASH) &&
                    tokens[0].get_value().size() >= 3)
                {
                    return "";
                }
            }
        }

        size_t index = 0;
        while (index++ < size)
        {
            if (index + 1 < size)
            {
                // If this token is an escape token, we may need to merge it with the next token.
                if (tokens[index].get_type() == token_type::ESCAPE)
                {
                    switch (tokens[index + 1].get_type())
                    {
                    // Tokens that we escape:
                    case token_type::DOLLAR:
                    case token_type::STAR:
                    case token_type::DASH:
                    case token_type::EQUALS:
                    case token_type::LT:
                    case token_type::GT:
                    case token_type::PIPE:
                    case token_type::TICK:
                        this->escape_next(tokens, index);
                        break;
                    // Tokens that we don't escape:
                    default:
                        tokens[index] = Token(token_type::TERMINAL, '\\');
                        break;
                    }
                    size = tokens.size();
                    // Since this token is now terminal, we go back to the top of the loop.
                    continue;
                }
            }
        }
        return this->parse(tokens);
    }

    // The input stream operator.
    //
    //   Parser parser;
    //   "# Hello, World!" >> parser;
    //
    // * std::istream &in     - The input stream.
    // * Parser &parser       - The parser.
    // * return std::istream& - The input stream.
    std::istream &operator>>(std::istream &is, Parser &parser)
    {
    }

    // The output stream operator.
    //
    //   Parser parser;
    //   // ...
    //   std::cout << parser;
    //
    // * std::ostream &out    - The output stream.
    // * const Parser &parser - The parser.
    // * return std::ostream& - The output stream.
    std::ostream &operator<<(std::ostream &os, const Parser &parser)
    {
    }

    // Consolidate the given vector of tokens.
    // Concatenate adjacent corresponding tokens into one.
    //
    // * std::vector<Token> &tokens - The vector of tokens.
    void Parser::consolidate(std::vector<Token> &tokens)
    {
        // Iterate through the tokens in the given vector by index.
        for (size_t index = 0; index + 1 < tokens.size(); index++)
        {
            // For the following types of tokens, if this token and the next token are both
            // of this type of token, merge them together.
            Parser::merge_next(tokens, index, token_type::TERMINAL);
            Parser::merge_next(tokens, index, token_type::SPACE);
            Parser::merge_next(tokens, index, token_type::EQUALS);
            Parser::merge_next(tokens, index, token_type::TICK);
            Parser::merge_next(tokens, index, token_type::NUMBER);
        }
    }

    // In a given vector of tokens, check whether the token at the given index
    // and the following token are both of the given type.
    // If they are, concatenate them into one token.
    //
    // * std::vector<Token> &tokens - The vector of tokens.
    // * const size_t &index        - The index of the token to merge.
    // * const token_type &type     - The type of the token to check.
    void Parser::merge_next(std::vector<Token> &tokens, const size_t &index, const token_type &type)
    {
        if (index + 1 < tokens.size())
        {
            if (tokens[index].get_type() == type && tokens[index + 1].get_type() == type)
            {
                tokens[index].merge(tokens[index + 1]);
                tokens.erase(tokens.begin() + index);
            }
        }
    }

    // In a given vector of tokens, delete the token at the given index
    // and escape the following token.
    //
    // * std::vector<Token> &tokens - The vector of tokens.
    // * size_t index               - The index of the token to delete.
    void Parser::escape_next(std::vector<Token> &tokens, size_t index)
    {
        if (index + 1 < tokens.size() && tokens[index].get_type() == token_type::ESCAPE)
        {
            tokens.erase(tokens.begin() + index);
            char escaped;
            switch (tokens[index].get_type())
            {
            case token_type::DOLLAR:
                escaped = '$';
                break;
            case token_type::STAR:
                escaped = '*';
                break;
            case token_type::DASH:
                escaped = '-';
                break;
            case token_type::EQUALS:
                escaped = '=';
                break;
            case token_type::LT:
                escaped = '<';
                break;
            case token_type::GT:
                escaped = '>';
                break;
            case token_type::PIPE:
                escaped = '|';
                break;
            case token_type::TICK:
                escaped = '`';
                break;
            default:
                throw std::runtime_error("Trying to escape a token that cannot be escaped!");
            }
            tokens[index] = Token(token_type::TERMINAL, escaped);
        }
    }
}
