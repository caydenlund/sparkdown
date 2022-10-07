/**
 * @file lexer/lexer.hpp
 * @package //lexer:lexer
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `lexer` class definition.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file defines the `lexer` class,
 *     which is used to lex a string into a sequence of tokens.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#ifndef LEXER_HPP
#define LEXER_HPP

#include <list>
#include <string>

#include "token/token.hpp"

namespace sparkdown {

/**
 * @brief Used to lex a string into a sequence of tokens.
 * @details
 *
 *     TODO: Add stream redirection operators.
 *
 */
class lexer {
   private:
    /**
     * @brief Contains the current sequence of tokens.
     *
     */
    std::list<token> _tokens;

   public:
    /**
     * @brief Constructor.
     *
     */
    lexer();

    /**
     * @brief Lexes the given string into a sequence of tokens.
     *
     * @param str The string to lex.
     */
    void lex(const std::string &str);

    /**
     * @brief Returns a copy of the token sequence and flushes the buffer.
     *
     * @return A copy of the token sequence.
     */
    std::list<token> get_tokens();
};

}  // namespace sparkdown

#endif