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

// TODO: Remove these temporary pragmas once we no longer need them.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#include "sparkdown.hpp"

#include <iostream>

sparkdown::sparkdown::sparkdown::sparkdown(const std::string &input_file,
                                           const std::string &output_file) {
    this->_input_file = input_file;
    this->_output_file = output_file;

    if (!this->_input_file.empty()) {
        // Ensure that the input file, if given, exists:
        if (!std::filesystem::exists(this->_input_file)) {
            std::cerr << "Error: input file \"" << input_file
                      << "\" does not exist. Exiting." << std::endl;
            exit(1);
        }

        // Ensure that the input file, if given, is not a directory:
        if (std::filesystem::is_directory(this->_input_file)) {
            std::cerr << "Error: input file \"" << input_file
                      << "\" is a directory. Exiting." << std::endl;
            exit(1);
        }
    }

    if (!this->_output_file.empty()) {
        // Ensure that the output file, if given, is not a directory:
        if (std::filesystem::is_directory(this->_output_file)) {
            std::cerr << "Error: output file \"" << output_file
                      << "\" is a directory. Exiting." << std::endl;
            exit(1);
        }
    }
}

void sparkdown::sparkdown::parse() {
    // TODO: Implement.
}

std::string sparkdown::sparkdown::get_latex_code() const {
    // TODO: Implement.

    // Just to avoid compiler warnings:
    return {};
}

void sparkdown::sparkdown::save_latex_code() const {
    // TODO: Implement.
}

void sparkdown::sparkdown::save_latex_code(const std::string &output) const {
    // TODO: Implement.
}

void sparkdown::sparkdown::save_latex_code(
    const std::filesystem::path &output) const {
    // TODO: Implement.
}

void sparkdown::sparkdown::save_latex_code(std::ostream &output) const {
    // TODO: Implement.
}

std::string sparkdown::sparkdown::version() { return {SPARKDOWN_VERSION}; }

#pragma clang diagnostic pop