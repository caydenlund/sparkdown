// src/mark-sideways/mark-sideways.cpp
// v. 0.4.0
//
// Author: Cayden Lund
//   Date: 10/05/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the functions
// for the mark-sideways library.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "parser/parser.hpp"
#include "mark-sideways.hpp"

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // Print usage information.
    //
    // * std::string program_name - The name of the program being executed.
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

    // Parse a mark-sideways file to stdout.
    //
    // * mark_sideways::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    void parse_file(mark_sideways::Parser parser, std::ifstream &input_file)
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

    // Parse a mark-sideways file to an output file.
    //
    // * mark_sideways::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    // * std::ofstream &output_file   - The output file for the LaTeX code.
    void parse_file(mark_sideways::Parser parser, std::ifstream &input_file, std::ofstream &output_file)
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
}
