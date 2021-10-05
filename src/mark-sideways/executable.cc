// src/mark-sideways/executable.cc
// v. 0.3.0
//
// Author: Cayden Lund
//   Date: 10/05/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the main program entry point.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

// Include our helper functions.
#include "mark-sideways.h"

// Main program entry point.
int main(int argc, char *argv[])
{
    // Make sure that the user provided at least one argument.
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    std::string input = "";
    std::string output = "";

    bool output_stdout = true;
    bool overwrite = false;

    // Parse the input arguments.
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            print_usage(argv[0]);
            return 0;
        }
        else if (arg == "-v" || arg == "--version")
        {
            print_version();
            return 0;
        }
        else if (arg == "-o" || arg == "--output")
        {
            if (i + 1 < argc)
            {
                output = argv[++i];
                output_stdout = false;
            }
            else
            {
                std::cout << "Error: Missing output file." << std::endl;
                return 1;
            }
        }
        else if (arg == "-w" || arg == "--overwrite")
        {
            overwrite = true;
        }
        else
        {
            input = arg;
        }
    }

    // Make sure that the user provided a file to parse.
    if (input == "")
    {
        print_usage(argv[0]);
        return 1;
    }

    // Make sure that the input file exists.
    if (!std::filesystem::exists(input))
    {
        std::cerr << "Error: File '" << input << "' does not exist." << std::endl;
        return 1;
    }

    // Make sure that the output file is not the same as the input file.
    if (input == output)
    {
        std::cerr << "Error: Input and output files cannot be the same." << std::endl;
        return 1;
    }

    // Make sure that the input and output files are not a directory.
    if (std::filesystem::is_directory(input))
    {
        std::cerr << "Error: Is a directory: " << input << std::endl;
        return 1;
    }
    if (std::filesystem::is_directory(output))
    {
        std::cerr << "Error: Is a directory: " << output << std::endl;
        return 1;
    }

    // If the output file exists, make sure that the user wants to overwrite it.
    if (std::filesystem::exists(output) && !overwrite)
    {
        std::cout << "Warning: Output file '" << output << "' already exists. Overwrite? (Y/n) ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "Y" || input == "y" || input == "")
        {
            overwrite = true;
        }
        else
        {
            std::cerr << "Error: Output file '" << output << "' already exists. Will not overwrite." << std::endl;
            return 1;
        }
    }

    // Open the input file.
    std::ifstream input_file(input);
    if (!input_file.is_open())
    {
        std::cerr << "Error: Could not open file '" << input << "'." << std::endl;
        return 1;
    }

    // Open the output file.
    std::ofstream output_file(output);
    if (!output_stdout && !output_file.is_open())
    {
        std::cerr << "Error: Could not open file '" << output << "'." << std::endl;
        return 1;
    }

    // Instantiate a new Parser object.
    Parser parser = Parser();

    // Parse the input file.
    if (output_stdout)
    {
        parse_file(parser, input_file);
    }
    else
    {
        parse_file(parser, input_file, output_file);
    }

    return 0;
}