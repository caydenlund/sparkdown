// src/sparkdown/sparkdown.cpp
// v. 0.4.1
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the functions
// for the sparkdown library.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "parser/parser.hpp"
#include "sparkdown.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
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

    // Parse a sparkdown file to stdout.
    //
    // * sparkdown::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    void parse_file(sparkdown::Parser parser, std::ifstream &input_file)
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

    // Parse a sparkdown file to an output file.
    //
    // * sparkdown::Parser parser - The parser to handle the input file.
    // * std::ifstream &input_file    - The file to parse.
    // * std::ofstream &output_file   - The output file for the LaTeX code.
    void parse_file(sparkdown::Parser parser, std::ifstream &input_file, std::ofstream &output_file)
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
