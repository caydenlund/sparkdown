/**
 * @file sparkdown/sparkdown.hpp
 * @package //sparkdown:sparkdown.lib
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `sparkdown` class definition.
 * @details This project is part of Sparkdown, a new markup language
 *     for quickly writing and formatting notes.
 *
 *     This file defines the `sparkdown` class, which serves as the public
 *     interface to the Sparkdown library.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

// TODO: Remove these temporary pragmas once we no longer need them.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#ifndef SPARKDOWN_HPP
#define SPARKDOWN_HPP

/**
 * @brief Sparkdown current version information.
 *
 */
#define SPARKDOWN_VERSION "v2.0.0"

#include <filesystem>
#include <string>
#include <vector>

namespace sparkdown {

/**
 * @brief The main driver class for Sparkdown.
 * @details This class provides the main driver class for both the library
 *     and the command-line interface.
 *
 *     Includes methods for inputting Sparkdown text
 *     and retrieving LaTeX output.
 *
 *     TODO: Add stream redirection operators.
 *
 */
class sparkdown {
   private:
    //  ++====================++
    //  ||  Member variables  ||
    //  ++====================++

    /**
     * @brief The file path to the Sparkdown file to parse.
     * @details May be left empty.
     *
     */
    std::string _input_file;

    /**
     * @brief The file path to the LaTeX output file.
     * @details May be left empty.
     *
     */
    std::string _output_file;

   public:
    //  ++====================++
    //  ||  Instance methods  ||
    //  ++====================++

    /**
     * @brief Constructor.
     *
     * @param input_file The file path to the Sparkdown file to parse.
     *     Leave empty for manual input.
     * @param output_file The file path to the LaTeX output file. If left empty,
     *     the output will be written to stdout.
     *     Leave empty for manual output.
     */
    explicit sparkdown(const std::string& input_file,
                       const std::string& output_file = "");

    /**
     * @brief Parses the input file.
     * @details Saves the data in the class structure for later use.
     *
     */
    void parse();

    /**
     * @brief Returns the LaTeX code for the parsed file as a string.
     * @details Must be called after `parse()`.
     *
     * @return The LaTeX code for the parsed file.
     */
    [[nodiscard]] std::string get_latex_code() const;

    /**
     * @brief Writes the stored LaTeX code to the output file.
     * @details The output file must have been saved from the constructor.
     *
     */
    void save_latex_code() const;

    /**
     * @brief Writes the stored LaTeX code to the output file.
     *
     * @param output The output file to write to.
     */
    void save_latex_code(const std::string& output) const;

    /**
     * @brief Writes the stored LaTeX code to the output file.
     *
     * @param output The output file to write to.
     */
    void save_latex_code(const std::filesystem::path& output) const;

    /**
     * @brief Writes the stored LaTeX code to an output stream.
     *
     * @param output The output stream to write to.
     */
    void save_latex_code(std::ostream& output) const;

    //  ++==================++
    //  ||  Static methods  ||
    //  ++==================++

    /**
     * @brief Returns the version information of the Sparkdown library.
     *
     * @return The version information of the Sparkdown library.
     */
    static std::string version();
};

}  // namespace sparkdown

#endif
#pragma clang diagnostic pop