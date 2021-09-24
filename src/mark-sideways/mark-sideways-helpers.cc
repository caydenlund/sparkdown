// src/mark-sideways/mark-sideways-helpers.cc
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 09/23/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains helper functions for the main mark-sideways executable.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "lib/parser/parser.h"
#include "mark-sideways-helpers.h"

// Print usage information.
void print_usage(std::string program_name)
{
    std::cout << "Usage: " << program_name << " <file> [OPTIONS]" << std::endl;
    std::cout << "  Options:" << std::endl;
    std::cout << "    -h, --help: \tPrint this help message." << std::endl;
    std::cout << "    -v, --version: \tPrint version information." << std::endl;
    std::cout << "    -o, --output: \tOutput file." << std::endl;
    std::cout << "    -w, --overwrite: \tOverwrite output file if it exists." << std::endl;
}

// Print version information.
void print_version()
{
    std::cout << "notes-parser v0.2.0" << std::endl;
    std::cout << "Cayden Lund <https://github.com/shrimpster00>" << std::endl;
}

// Parse a file to stdout.
void parse_file(Parser parser, std::ifstream &input_file)
{
    std::string line;

    std::getline(input_file, line);
    input_file.seekg(0);

    if (line[0] == '$')
    {
        while (parser.is_head())
        {
            std::getline(input_file, line);
            parser.parse_headline(line);
        }
    }

    std::cout << parser.start() << std::endl;

    while (std::getline(input_file, line))
    {
        std::cout << parser.parse_line(line) << std::endl;
    }

    std::cout << parser.end() << std::endl;
}

// Parse a file to another file.
void parse_file(Parser parser, std::ifstream &input_file, std::ofstream &output_file)
{
    std::string line;

    std::getline(input_file, line);
    input_file.seekg(0);

    if (line[0] == '$')
    {
        while (parser.is_head())
        {
            std::getline(input_file, line);
            parser.parse_headline(line);
        }
    }

    output_file << parser.start() << std::endl;

    while (std::getline(input_file, line))
    {
        output_file << parser.parse_line(line) << std::endl;
    }

    output_file << parser.end() << std::endl;
}
