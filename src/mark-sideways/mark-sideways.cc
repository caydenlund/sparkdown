#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "lib/parser/parser.h"

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
    std::cout << "notes-parser v0.1.0" << std::endl;
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
