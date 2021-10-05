// src/parser/parser.hpp
// v. 0.3.1
//
// Author: Cayden Lund
//   Date: 10/05/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the Parser class.
// See parser.cc for implementation and documentation.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <regex>

// We use the State class to keep track of the current state of the parser.
#include "state.hpp"

// A class to parse an input set of mark-sideways strings into LaTeX code.
class Parser
{
public:
    Parser();
    std::string start();
    std::string end();
    bool is_head();
    void parse_headline(std::string line);
    std::string parse_line(std::string line);

protected:
    State state;
    bool head;
    std::string title;
    std::string author;
    std::string date;
    std::regex headline_regex;
    std::regex title_regex;
    std::regex author_regex;
    std::regex date_regex;
    std::regex section_regex;
    std::regex indentation_regex;
    std::regex itemize_regex;
    std::regex enumerate_regex;
    std::regex bold_regex;
    std::regex italic_regex;
    std::regex verb_regex;
    std::regex verbatim_regex;
    std::regex arrow_regex;
    std::regex section_char_regex;
    void parse_section();
    void parse_indentation();
    void parse_itemize();
    void parse_enumerate();
    void parse_bold();
    void parse_italics();
    void parse_verb();
    void parse_verbatim();
    void parse_arrow();
};

#endif