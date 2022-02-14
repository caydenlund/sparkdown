// //parser
//
// Author: Cayden Lund
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

namespace sparkdown
{
    // Parser
    //    Used to parse a string of sparkdown into a string of LaTeX.
    //
    //    There are two ways to use the Parser class:
    //       1. Use the parse() method.
    //          Example:
    //             Parser parser;
    //             std::string latex = parser.parse("# Hello, World!") + parser.end();
    //       2. Use the stream operators.
    //          Example:
    //             Parser parser;
    //             std::stringstream ss;
    //             "# Hello, World!" >> parser;
    //             ss << parser << parser.end();
    //             std::string latex = ss.str();

    // =======================
    // ||  Public methods:  ||
    // =======================

    // constructor
    //    Takes no arguments.
    Parser::Parser() : latex(), packages()
    {
        packages.insert("amsmath");
    }

    // parse
    //    Takes a string of sparkdown and returns a string of LaTeX.
    //
    // Arguments:
    //    const std::string &line - The string of sparkdown to parse.
    //
    // Returns:
    //    std::string - The string of LaTeX.
    std::string Parser::parse(const std::string &input)
    {
        std::vector<Token> tokens = lex(input);
        return this->parse(tokens);
    }

    // operator >>
    //    The stream operator for parsing.
    //
    // Example:
    //    Parser parser;
    //    "# Hello, World!" >> parser;
    //
    // Parameters:
    //    std::istream &is - The input stream.
    //    Parser &parser   - The parser in action.
    //
    // Returns:
    //    std::istream & - The input stream.
    std::istream &operator>>(std::istream &is, Parser &parser)
    {
    }

    // operator <<
    //    The stream operator for output.
    //
    // Example:
    //    Parser parser;
    //    // ...
    //    std::cout << parser << parser.end();
    //
    // Parameters:
    //    std::ostream &os     - The output stream.
    //    const Parser &parser - The parser in action.
    //
    // Returns:
    //    std::ostream & - The output stream.
    std::ostream &operator<<(std::ostream &os, const Parser &parser)
    {
    }

    // is_head
    //    Indicates whether or not we are still parsing the head of the document.
    //
    // Returns:
    //    bool - True when we are still parsing the head of the document.
    bool Parser::is_head()
    {
        return this->in_head;
    }

    // end
    //    Indicates to the parser that the file has finished being read.
    //
    // Returns:
    //    std::string - The ending LaTeX (including the `\end{document}`).
    std::string Parser::end()
    {
        return "";
    }

    // ========================
    // ||  Private methods:  ||
    // ========================

    // parse
    //    Parses the given vector of tokens.
    //
    // Arguments:
    //    std::vector<Token> &tokens - The vector of tokens to parse.
    //
    // Returns:
    //    std::string - The LaTeX.
    std::string Parser::parse(std::vector<Token> &tokens)
    {
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

    // set_property
    //    Sets a property of the document.
    //
    // Arguments:
    //    const std::string &property - The property to set.
    //    const std::string &value    - The new value of the property.
    void Parser::set_property(const std::string &property, const std::string &value)
    {
        if (property == "author")
        {
            this->author = value;
        }
        else if (property == "title")
        {
            this->title = value;
        }
        else if (property == "date")
        {
            this->date = value;
        }
        else if (property == "usepackage" || property == "usePackage")
        {
            this->packages.insert(value);
        }
    }

    // escape_next
    //    In a given vector of tokens, deletes the token at the given index
    //    and escapes the following token.
    //
    // Arguments:
    //    std::vector<Token> &tokens - The vector of tokens.
    //    const size_t &index        - The index of the token to escape.
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
