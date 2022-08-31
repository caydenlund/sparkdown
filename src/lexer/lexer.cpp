/**
 * @file lexer/lexer.cpp
 * @package //lexer:lexer
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `lexer` class implementation.
 * @details This project is part of Sparkdown, a new markup language
 *     for quickly writing and formatting notes.
 *
 *     This file implements the `lexer` class,
 *     which is used to lex a string into a sequence of tokens.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#include "lexer.hpp"

namespace sparkdown {

lexer::lexer() = default;

void lexer::lex(const std::string &str) {
    for (char c : str) {
        this->_tokens.emplace_back(c);
    }
}

std::vector<token> lexer::get_tokens() {
    std::vector<token> tokens(this->_tokens);

    this->_tokens.clear();

    return tokens;
}

}  // namespace sparkdown
