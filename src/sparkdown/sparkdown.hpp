// //sparkdown
// v. 0.4.2
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the definitions for the library methods.
// See sparkdown.cc for implementation.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#ifndef SPARKDOWN_HPP
#define SPARKDOWN_HPP

#include <string>

#include "parser/parser.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // Print usage information.
    //
    // * std::string program_name - The name of the program being executed.
    void print_usage(std::string program_name);

    // Print version information.
    void print_version();

    // Parse a sparkdown file to stdout.
    //
    // * sparkdown::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    void parse_file(sparkdown::Parser parser, std::ifstream &input_file);

    // Parse a sparkdown file to an output file.
    //
    // * sparkdown::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    // * std::ofstream &output_file   - The output file for the LaTeX code.
    void parse_file(sparkdown::Parser parser, std::ifstream &input_file, std::ofstream &output_file);
}

#endif