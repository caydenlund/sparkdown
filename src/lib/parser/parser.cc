// src/lib/parser/parser.cc
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 09/23/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the Parser class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// This is the header file for the Parser class.
#include "lib/parser/parser.h"

// We also use the State class.
#include "lib/parser/state.h"

// TODO: \item indentation.
// TODO: ``` indentation.
// TODO: Ignore symbols in math mode, verbatim.

Parser::Parser()
{
    state = State();
    head = true;
    title = "Notes";
    author = "Cayden Lund";
    date = "";
    headline_regex = std::regex("^=+");
    title_regex = std::regex("^\\$title: ");
    author_regex = std::regex("^\\$author: ");
    date_regex = std::regex("^\\$date: ");
    section_regex = std::regex("^(\\#+) ");
    indentation_regex = std::regex("^(\\s*)(\\S+?)");
    itemize_regex = std::regex("^(\\s*)[\\*\\-]\\s+");
    enumerate_regex = std::regex("^(\\s*)\\d+[\\.\\)]\\s+");
    bold_regex = std::regex("\\*\\*(.*?)\\*\\*");
    italic_regex = std::regex("\\*(.*?)\\*");
    verbatim_regex = std::regex("```");
    verb_regex = std::regex("([\\|])(.*?)\\1");
    arrow_regex = std::regex("[\\-=]+>");
    section_char_regex = std::regex("§");
}

// Returns the headers for a new file.
std::string Parser::start()
{
    std::string header = "";

    header += "\\title{" + title + "}\n";
    header += "\\author{" + author + "}\n";
    header += "\\date{" + date + "}\n\n";

    header += "\\documentclass[12pt, letterpaper]{article}\n\n\n";

    header += "\\usepackage{graphicx}\n";
    header += "\\graphicspath{{.}}\n\n";
    header += "\\usepackage[utf8]{inputenc}\n\n";
    header += "\\usepackage{tabularx}\n\n";
    header += "\\usepackage{amsmath}\n\n\n";

    header += "\\begin{document}\n\n\n";

    header += "\\maketitle\n\n";

    return header;
}

// Returns the footers for a new file.
std::string Parser::end()
{
    std::string footer = "";
    state.begin_itemize(0);
    footer += state.get_product();
    footer += "\n\n\\end{document}";
    return footer;
}

// Returns true when we are currently parsing the head of the file.
bool Parser::is_head()
{
    return head;
}

// Parse the sections of the file.
void Parser::parse_section()
{
    std::string line = state.get_line();
    std::smatch match;
    if (std::regex_search(line, match, section_regex))
    {
        std::string section = "\\";
        int level = match.str(1).length();
        for (int i = 0; i < level - 1; i++)
        {
            section += "sub";
        }
        section += "section*{";
        line = std::regex_replace(line, section_regex, section);
        line += "}";
    }
    state.set_line(line);
}

// Parse indentation.
void Parser::parse_indentation()
{
    std::smatch match;
    std::string line = state.get_line();
    if (std::regex_search(line, match, indentation_regex) && !std::regex_search(line, itemize_regex) && !std::regex_search(line, enumerate_regex))
    {
        int indentation = match.str(1).length() / 2;
        state.set_indentation(indentation);
        std::regex_replace(line, indentation_regex, "$2");
    }
}

// Parse for bullet points.
void Parser::parse_itemize()
{
    std::smatch match;
    std::string line = state.get_line();
    if (std::regex_search(line, match, itemize_regex))
    {
        int indentation = match.str(1).length() / 2;
        state.begin_itemize(indentation + 1);
        state.set_line(std::regex_replace(line, itemize_regex, "\\item "));
    }
}

// Parse for numbered lists.
void Parser::parse_enumerate()
{
    std::smatch match;
    std::string line = state.get_line();
    if (std::regex_search(line, match, enumerate_regex))
    {
        int indentation = match.str(1).length() / 2;
        state.begin_enumerate(indentation + 1);
        state.set_line(std::regex_replace(line, enumerate_regex, "\\item "));
    }
}

// Replace all bold text with LaTeX code.
void Parser::parse_bold()
{
    std::string line = state.get_line();
    while (std::regex_search(line, bold_regex))
    {
        line = std::regex_replace(line, bold_regex, "\\textbf{$1}");
    }
    state.set_line(line);
}

// Replace all italic text with LaTeX code.
void Parser::parse_italics()
{
    std::string line = state.get_line();
    while (std::regex_search(line, italic_regex))
    {
        line = std::regex_replace(line, italic_regex, "\\textit{$1}");
    }
    state.set_line(line);
}

// Replace all inline verbatim text with LaTeX code.
void Parser::parse_verb()
{
    std::string line = state.get_line();
    while (std::regex_search(line, verb_regex))
    {
        line = std::regex_replace(line, verb_regex, "\\verb§$2§");
    }
    state.set_line(std::regex_replace(line, section_char_regex, "|"));
}

// Replace all blocks of verbatim text with LaTeX code.
void Parser::parse_verbatim()
{
    std::string line = state.get_line();
    while (std::regex_search(line, verbatim_regex))
    {
        line = std::regex_replace(line, verbatim_regex, state.toggle_verbatim());
    }
    state.set_line(line);
}

// Parse for arrows.
void Parser::parse_arrow()
{
    std::string line = state.get_line();
    std::smatch match;
    int i = 0;
    bool in_math_mode = false;
    while (std::regex_search(line, match, arrow_regex))
    {
        int position = match.position();
        while (i < position)
        {
            if (line[i] == '$')
            {
                in_math_mode = !in_math_mode;
            }
            i++;
        }
        if (in_math_mode)
        {
            line = std::regex_replace(line, arrow_regex, "\\rightarrow");
        }
        else
        {
            line = std::regex_replace(line, arrow_regex, "$\\rightarrow$");
        }
    }
    state.set_line(line);
}

// Parse a single line from the head of the file.
void Parser::parse_headline(std::string line)
{
    if (std::regex_search(line, headline_regex))
    {
        head = false;
        return;
    }
    if (std::regex_search(line, title_regex))
    {
        title = std::regex_replace(line, title_regex, "");
    }
    else if (std::regex_search(line, author_regex))
    {
        author = std::regex_replace(line, author_regex, "");
    }
    else if (std::regex_search(line, date_regex))
    {
        date = std::regex_replace(line, date_regex, "");
    }
}

// Parse a single line from the input file.
std::string Parser::parse_line(std::string line)
{
    state.set_line(line);
    parse_verbatim();
    if (!state.is_verbatim())
    {
        parse_section();
        parse_indentation();
        parse_itemize();
        parse_enumerate();
        parse_bold();
        parse_italics();
        parse_verb();
        parse_arrow();
    }
    return state.get_product();
}
