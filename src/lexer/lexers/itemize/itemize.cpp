// src/lexer/lexers/itemize/itemize.cpp
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 10/06/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation for the bullet point lexer.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

// System imports.
#include <string>
#include <regex>

// The itemize header file.
#include "itemize.hpp"

// We use the State class to keep track of the current state of the parser.
#include "parser/state.hpp"

// The interface for a lexer.
#include "lexer/lexers/abstractLexer/abstractLexer.hpp"

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
        mark_sideways::lexers::Itemize::Itemize(mark_sideways::State *state) : AbstractLexer(state)
        {
            // The regex for the bullet point lexer.
            this->match_regex = std::regex("^(\\s*)[-\\*](\\s.*)");
            this->escape_regex = std::regex("^(\\s*)\\\\([-\\*]\\s.*)");
        }

        // The class destructor.
        mark_sideways::lexers::Itemize::~Itemize()
        {
            // Nothing to do here.
        }

        // Returns true when a given line is a bullet point.
        //
        // * std::string line - The line to check.
        // * return bool      - True if the line is a bullet point.
        bool mark_sideways::lexers::Itemize::is_bullet_point(std::string line)
        {
            if (this->ignore(line))
                return false;
            return std::regex_search(line, this->match_regex);
        }

        // lex() is used to lex a single input line.
        // This method takes in a string and returns a new string with the lexed tokens.
        //
        // * std::string line   - The string to lex.
        // * return std::string - The lexed string.
        std::string mark_sideways::lexers::Itemize::lex(std::string line)
        {
            // First, determine whether we are in a block of verbatim text or math mode.
            if (!this->ignore(line))
            {
                // If we are not in verbatim or math mode, then we can test whether the line is a bullet point.
                if (std::regex_search(line, this->match_regex))
                {
                    // We can lex the line if it matches the regex.
                    std::string bullet_indentation = std::regex_replace(line, this->match_regex, "$1");
                    int bullet_point_level = (bullet_indentation.length() / 2) + 1;

                    std::string bullet_content = std::regex_replace(line, this->match_regex, "$2");

                    return get_token(bullet_point_level) + bullet_content;
                }
                else if (std::regex_search(line, this->escape_regex))
                {
                    // Otherwise, if the line matches the escape regex, then we delete the escape character.
                    return std::regex_replace(line, this->escape_regex, "$1$2");
                }
            }
            // Otherwise, return the line unchanged.
            return line;
        }

        // ignore() returns true when we should ignore the given line.
        //
        // * std::string line - The line to test.
        // * return bool      - Whether we should ignore the given line.
        bool mark_sideways::lexers::Itemize::ignore(std::string line)
        {
            return (state->is_verbatim() || state->is_math());
        }

        // The token used to replace the bullet point.
        // The token is of the form "[%%==BULLET_{LEVEL}==%%]", where {LEVEL} is the bullet point level.
        //
        // * int level - The level of the bullet point.
        std::string mark_sideways::lexers::Itemize::get_token(int level)
        {
            return "[%%BULLET=" + std::to_string(level) + "%%]";
        }
    }
}
