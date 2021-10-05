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

// Parser.
// This class is used to parse a set of strings formatted as mark-sideways into a set of strings of LaTeX.
// The mark-sideways text is parsed line by line, and as we read each line, we update the state accordingly.
// Upon reading the line, we use the state to determine what to do with the line.
// We then return a string of LaTeX to the caller.
//
// The mark-sideways rules are as follows:
//
//   1.  #  A headline.
//       ## A sub-headline.
//   2.  *  A bullet point.
//       -  A bullet point.
//   3.  1. Item of a numbered list.
//   4.  **Inline bold text.**
//   5.  *Inline italic text.*
//   6.  ```
//       Block of verbatim text.
//       ```
//   7.  |Inline verbatim text.|
//   8.  -> Rightarrow.
//       => Rightarrow.

// The constructor for the Parser class.
// It accepts no arguments and has some default values.
// Overrides of these defaults are specified
// inside the mark-sideways text itself.
Parser::Parser()
{
    // Set the default Parser state.
    state = State();

    // Assume at first that we are reading overrides for the head of the document.
    head = true;
    // Default values.
    title = "Notes";
    author = "Cayden Lund";
    date = "";

    // A line starting with '=' signals that we are no longer reading overrides
    // in the head of the document.
    headline_regex = std::regex("^=+");

    // We use $title, $author, and $date commands to set the title, author, and date of the document.
    title_regex = std::regex("^\\$title: ");
    author_regex = std::regex("^\\$author: ");
    date_regex = std::regex("^\\$date: ");

    // 1. # Headline.
    section_regex = std::regex("^(\\#+) ");

    // (Handle indentation.)
    indentation_regex = std::regex("^(\\s*)(\\S+?)");

    // 2. * Bullet point.
    itemize_regex = std::regex("^(\\s*)[\\*\\-]\\s+");

    // 3. (\d). Ordered list.
    enumerate_regex = std::regex("^(\\s*)\\d+[\\.\\)]\\s+");

    // 4. **Bold text.**
    bold_regex = std::regex("\\*\\*(.*?)\\*\\*");

    // 5. *Italic text.*
    italic_regex = std::regex("\\*(.*?)\\*");

    // 6. ```
    //    Block of verbatim text.
    //    ```
    verbatim_regex = std::regex("```");

    // 7. |Inline verbatim text.|
    verb_regex = std::regex("([\\|])(.*?)\\1");

    // 8. -> Rightarrow.
    arrow_regex = std::regex("[\\-=]+>");

    // We use the section symbol internally to indicate
    // sections of the string as we parse it.
    section_char_regex = std::regex("§");
}

// Returns the LaTeX headers for a new file,
// using our `title`, `author`, and `date` instance variables.
// TODO: Use a string stream instead of a string.
std::string Parser::start()
{
    std::string header = "";

    // \title{Notes}
    header += "\\title{" + title + "}\n";

    // \author{Cayden Lund}
    header += "\\author{" + author + "}\n";

    // \date{}
    header += "\\date{" + date + "}\n\n";

    // \documentclass[12pt, letterpaper]{article}
    header += "\\documentclass[12pt, letterpaper]{article}\n\n\n";

    // \usepackage{graphicx}
    // This allows us to include images.
    header += "\\usepackage{graphicx}\n";
    // \graphicspath{{.}}
    header += "\\graphicspath{{.}}\n\n";

    // \usepackage[utf8]{inputenc}
    // This allows us to use UTF-8 characters.
    header += "\\usepackage[utf8]{inputenc}\n\n";

    // \usepackage{tabularx}
    // For better tables.
    header += "\\usepackage{tabularx}\n\n";

    // \usepackage{amsmath}
    // For math mode.
    header += "\\usepackage{amsmath}\n\n\n";

    // \begin{document}
    header += "\\begin{document}\n\n\n";

    // \maketitle
    header += "\\maketitle\n\n";

    return header;
}

// Returns the footers for a new file.
// TODO: Use a string stream instead of a string.
std::string Parser::end()
{
    std::string footer = "";

    // Tell the state to add the closing tags
    // for any unclosed lists (i.e., bullet points and numbered lists).
    state.begin_itemize(0);
    footer += state.get_product();

    // \end{document}
    footer += "\n\n\\end{document}";

    return footer;
}

// Returns true while we are currently parsing the head of the file.
bool Parser::is_head()
{
    return head;
}

// Parse headlines.
// TODO: When we're in a headline, don't follow the rules for the rest of the document.
void Parser::parse_section()
{
    // Get the line from the state.
    std::string line = state.get_line();

    // If the line is in the format `#[#...] ...`,
    // then we are in a headline.
    std::smatch match;
    if (std::regex_search(line, match, section_regex))
    {
        std::string section = "\\";

        // Calculate whether we are in a sub-headline (or a sub-sub-headline, etc.) ...
        int level = match.str(1).length();
        // ... and add the appropriate number of 'sub's to the LaTeX command.
        for (int i = 0; i < level - 1; i++)
        {
            section += "sub";
        }

        // Replace `line` with the LaTeX command for the headline:
        // \[sub]section*{...}
        section += "section*{";
        line = std::regex_replace(line, section_regex, section);
        line += "}";
    }

    state.set_line(line);
}

// Parse indentation.
// TODO: Document.
void Parser::parse_indentation()
{
    // Get the line from the state.
    std::string line = state.get_line();

    std::smatch match;
    if (std::regex_search(line, match, indentation_regex) && !std::regex_search(line, itemize_regex) && !std::regex_search(line, enumerate_regex))
    {
        int indentation = match.str(1).length() / 2;
        state.set_indentation(indentation);
        std::regex_replace(line, indentation_regex, "$2");
    }
}

// Parse for bullet points.
// TODO: Document.
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
// TODO: Document.
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
    // Get the line from the state.
    std::string line = state.get_line();

    // Replace all bold text with LaTeX code:
    //
    // ``As long as there is still a part of the string
    //   that matches the pattern **...**, replace it
    //   with the LaTeX command for bold text.''
    //
    while (std::regex_search(line, bold_regex))
    {
        // \textbf{...}
        line = std::regex_replace(line, bold_regex, "\\textbf{$1}");
    }

    state.set_line(line);
}

// Replace all italic text with LaTeX code.
void Parser::parse_italics()
{
    // Get the line from the state.
    std::string line = state.get_line();

    // Replace all italic text with LaTeX code:
    //
    // ``As long as there is still a part of the string
    //   that matches the pattern *...*, replace it
    //   with the LaTeX command for italic text.''
    //
    while (std::regex_search(line, italic_regex))
    {
        // \textit{...}
        line = std::regex_replace(line, italic_regex, "\\textit{$1}");
    }

    state.set_line(line);
}

// Replace all inline verbatim text with LaTeX code.
void Parser::parse_verb()
{
    // Get the line from the state.
    std::string line = state.get_line();

    // Replace all inline verbatim text with LaTeX code:
    //
    // ``As long as there is still a part of the string
    //   that matches the pattern |...|, replace it
    //   with the LaTeX command for inline verbatim text.''
    //
    while (std::regex_search(line, verb_regex))
    {
        // \verb§...§
        // Note: The '|' is escaped with '§'.
        //       This is because the '|' is used in the regex.
        //       We do this in an effort to prevent an infinite loop.
        line = std::regex_replace(line, verb_regex, "\\verb§$2§");
    }

    // And now that we're out of the loop, we can replace the '§' with '|':
    // \verb|...|
    state.set_line(std::regex_replace(line, section_char_regex, "|"));
}

// Replace all blocks of verbatim text with LaTeX code.
// TODO: Correctly handle indentation and itemize/enumerate.
void Parser::parse_verbatim()
{
    // Get the line from the state.
    std::string line = state.get_line();
    while (std::regex_search(line, verbatim_regex))
    {
        // We tell the state to begin a verbatim block, or to end one if it is already in one.
        // \begin{verbatim}
        // \end{verbatim}
        line = std::regex_replace(line, verbatim_regex, state.toggle_verbatim());
    }
    state.set_line(line);
}

// Parse for arrows.
void Parser::parse_arrow()
{
    // Get the line from the state.
    std::string line = state.get_line();

    // \rightarrow is only valid in the context of a formula.
    // That means that we need to determine whether we are in a formula,
    // and if we aren't, we need to start one.
    std::smatch match;
    int i = 0;
    bool in_math_mode = false;
    while (std::regex_search(line, match, arrow_regex))
    {
        int position = match.position();
        // We iterate through the line until the index of the arrow,
        // toggling the math mode flag whenever we encounter a '$'.
        for (; i < position; i++)
        {
            if (line[i] == '$')
            {
                in_math_mode = !in_math_mode;
            }
        }
        if (in_math_mode)
        {
            // We don't need to start a new equation if we're already in one;
            // we just need to add the arrow.
            // \rightarrow
            line = std::regex_replace(line, arrow_regex, "\\rightarrow");
        }
        else
        {
            // We do need to start a new equation if we're not already in one.
            // $\rightarrow$
            line = std::regex_replace(line, arrow_regex, "$\\rightarrow$");
        }
    }

    state.set_line(line);
}

// Parse a single line from the head of the file.
// TODO: Document.
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
// TODO: Document.
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
