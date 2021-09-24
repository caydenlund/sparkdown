// src/mark-sideways/mark-sideways-helpers.h
// v. 0.2.0
//
// Author: Cayden Lund
//   Date: 09/23/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains helper functions for the main mark-sideways executable.
// See mark-sideways-helpers.cc for implementation and documentation.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef MARK_SIDEWAYS_HELPERS_H
#define MARK_SIDEWAYS_HELPERS_H

#include <string>

#include "lib/parser/parser.h"

// Print usage information.
void print_usage(std::string program_name);

// Print version information.
void print_version();

// Parse a mark-sideways file to stdout.
void parse_file(Parser parser, std::ifstream &input_file);

// Parse a mark-sideways file to an output file.
void parse_file(Parser parser, std::ifstream &input_file, std::ofstream &output_file);

#endif