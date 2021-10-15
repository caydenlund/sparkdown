// src/lexer/lexers/section/section.cpp
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/15/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the section lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// The section header file.
#include "section.hpp"

// We use the State class to keep track of the current state of the parser.
#include "state/state.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstract-lexer/abstract-lexer.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // The lexers namespace contains all the sub-lexer classes.
    namespace lexers
    {
        // The constructor saves a reference to the State object, which is used to store
        // the current state of the parser.
        //
        // mark_sideways::State state - The state object.
        mark_sideways::lexers::Section::Section(mark_sideways::State *state) : AbstractLexer(state)
        {
            this->match_regex = std::regex("^(#+) ([^\\n]+)\\n?$");
            this->escape_regex = std::regex("^\\\\(#+)([^]+)$");
        }

        // The class destructor.
        mark_sideways::lexers::Section::~Section()
        {
            // Nothing to do here.
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new vector with the lexed tokens.
        //
        // * std::string line                         - The string to lex.
        // * return std::vector<mark_sideways::Token> - The vector of tokens.
        std::vector<mark_sideways::Token> mark_sideways::lexers::Section::lex(std::string line)
        {
            // The vector of tokens to return.
            std::vector<mark_sideways::Token> tokens;

            // If the line matches the regex, then we are lexing a section headline.
            if (std::regex_match(line, this->match_regex))
            {
                // The section level is the number of hashes in the first group.
                int section_level = std::regex_replace(line, this->match_regex, "$1").length();

                // The section title is the second group.
                std::string section_title = std::regex_replace(line, this->match_regex, "$2");

                // Add the section token.
                tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::SECTION, "LEVEL=" + std::to_string(section_level) + ",TITLE=" + section_title));
            }
            else if (std::regex_match(line, this->escape_regex))
            {
                std::string escaped_hashes = std::regex_replace(line, this->escape_regex, "$1");
                std::string rest = std::regex_replace(line, this->escape_regex, "$2");

                tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::TEXT_CONTENT, escaped_hashes));
                tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, rest));
            }
            else
            {
                // If the line does not match the regex, then we add it back as an unlexed token.
                tokens.push_back(mark_sideways::Token(mark_sideways::Token::token_type::UNLEXED, line));
            }

            return tokens;
        }
    }
}
