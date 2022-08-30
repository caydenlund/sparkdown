/**
 * @file sparkdown/executable.cpp
 * @package //sparkdown:sparkdown
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief Sparkdown command-line interface.
 * @details This project is part of Sparkdown, a new markup language
 *     for quickly writing and formatting notes.
 *
 *     This file contains the main program entry point.
 *
 *     Usage of this program:
 *
 *         The filename is passed as a regular command-line argument:
 *
 *             `sparkdown file._`
 *
 *             Optionally, the filename can be omitted and Sparkdown
 *             will read the file contents from stdin.
 *
 *             Output is written to stdout by default.
 *
 *         The argument `-o`, or `--out`, instructs Sparkdown to
 *         write the output to the specified file.
 *
 *             `sparkdown file._ --out file.tex`
 *
 *             Output is then written to the specified file.
 *
 *         The argument `-w`, or `--watch`, instructs Sparkdown to
 *         watch the input file for changes.
 *
 *             `sparkdown file._ --watch`
 *
 *             `sparkdown file._ -w -o file.tex`
 *
 *             Whenever `file._` is modified, Sparkdown will re-parse
 *             the file and write the output to the specified location.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#include <iostream>

#include "arg.h/arg.h"
#include "sparkdown.hpp"

/**
 * @brief Main program entry point.
 *
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return 0 on success; 1 on failure.
 */
int main(int argc, char **argv) {
    argh arguments(argc, argv);

    if (arguments["-h"] || arguments["--help"]) {
        std::cout
            << "Usage:" << std::endl
            << "    sparkdown <input file> [options]" << std::endl
            << std::endl
            << "Options:" << std::endl
            << "    -o <output file>     --  Output the parsed file to the "
               "given file instead"
            << std::endl
            << "    --out <output file>      of stdout." << std::endl
            << std::endl
            << "    -w  /  --watch       --  Watch the input file for changes."
            << std::endl
            << "                             Whenever the file is modified,"
            << std::endl
            << "                             Sparkdown will re-parse the file "
               "and write the"
            << std::endl
            << "                             output to the proper location."
            << std::endl;
    }

    if (arguments["-v"] || arguments["--version"]) {
        std::cout << "Sparkdown" << std::endl
                  << "Version: " << sparkdown::sparkdown::version() << std::endl
                  << "Copyright (C) 2021-2022 by Cayden Lund." << std::endl
                  << "License: MIT <https://opensource.org/licenses/MIT>"
                  << std::endl;
    }

    std::string output = "";
    if (arguments["-o"]) output = arguments("-o");
    if (arguments["--out"]) output = arguments("--out");

    std::string input = arguments[1];

    sparkdown::sparkdown driver(input, output);
}
