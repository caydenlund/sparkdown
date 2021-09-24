#ifndef PARSER_H
#define PARSER_H

#include "lib/parser/state.h"

#include <string>
#include <regex>

// A class to parse an input file to LaTeX code.
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