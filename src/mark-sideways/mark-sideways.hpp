// src/mark-sideways/mark-sideways.hpp
// v. 0.4.0
//
// Author: Cayden Lund
//   Date: 10/05/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the definitions for the library methods.
// See mark-sideways.cc for implementation.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef MARK_SIDEWAYS_HELPERS_HPP
#define MARK_SIDEWAYS_HELPERS_HPP

#include <string>

#include "parser/parser.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // Print usage information.
    //
    // * std::string program_name - The name of the program being executed.
    void print_usage(std::string program_name);

    // Print version information.
    void print_version();

    // Parse a mark-sideways file to stdout.
    //
    // * mark_sideways::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    void parse_file(mark_sideways::Parser parser, std::ifstream &input_file);

    // Parse a mark-sideways file to an output file.
    //
    // * mark_sideways::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    // * std::ofstream &output_file   - The output file for the LaTeX code.
    void parse_file(mark_sideways::Parser parser, std::ifstream &input_file, std::ofstream &output_file);
}

#endif