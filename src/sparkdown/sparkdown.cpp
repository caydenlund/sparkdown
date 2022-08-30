/**
 * @file sparkdown/sparkdown.cpp
 * @package //sparkdown:sparkdown.lib
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `sparkdown` class definition.
 * @details This project is part of Sparkdown, a new markup language
 *     for quickly writing and formatting notes.
 *
 *     This file implements the `sparkdown` class, which serves as the public
 *     interface to the Sparkdown library.
 *
 *     See the header file for documentation.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

// TODO: Remove these temporary definitions.
#define c_green "\e[0;32m"
#define c_reset "\e[0m"
#define dbg std::cout << c_green << "[DEBUG]  " << c_reset

#include "sparkdown.hpp"

#include <iostream>

sparkdown::sparkdown(const std::string &input_file,
                     const std::string &output_file) {
    if (input_file == "") {
        // TODO: stdin.
    }

    if (!std::filesystem::exists(input_file)) {
        std::cerr << "Error: input file \"" << input_file
                  << "\" does not exist. Exiting." << std::endl;
        exit(1);
    }

    if (std::filesystem::is_directory(input_file)) {
        std::cerr << "Error: input file \"" << input_file
                  << "\" is a directory. Exiting." << std::endl;
        exit(1);
    }

    this->_input_file = std::filesystem::path(input_file);

    if (output_file != "") {
        if (std::filesystem::is_directory(output_file)) {
            std::cerr << "Error: output file \"" << output_file
                      << "\" is a directory. Exiting." << std::endl;
            exit(1);
        }
    }
}

void sparkdown::parse() {
    // TODO: Implement.
}

sparkdown::saved_latex_code_t sparkdown::get_latex_code() const {
    // TODO: Implement.

    // Just to avoid compiler warnings:
    return saved_latex_code_t();
}

void sparkdown::save_latex_code() const {
    // TODO: Implement.
}

void sparkdown::save_latex_code(const std::string &output) const {
    // TODO: Implement.
}

void sparkdown::save_latex_code(const std::filesystem::path &output) const {
    // TODO: Implement.
}

void sparkdown::save_latex_code(std::ostream &output) const {
    // TODO: Implement.
}

std::string sparkdown::version() { return std::string(SPARKDOWN_VERSION); }
