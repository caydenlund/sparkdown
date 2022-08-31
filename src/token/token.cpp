/**
 * @file token/token.cpp
 * @package //token:token
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `token` class definition.
 * @details This project is part of Sparkdown, a new markup language
 *     for quickly writing and formatting notes.
 *
 *     This file implements the `token` class, which represents a single token
 *     in the lexing/parsing process.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#include "token.hpp"

namespace sparkdown {

token::token(char character) : type(get_type(character)), value(character) {}

token::token(const token &other) = default;

bool token::operator==(const token &other) const {
    return type == other.type && value == other.value;
}

bool token::operator!=(const token &other) const { return !(*this == other); }

token_type token::get_type(char character) {
    switch (character) {
        case ' ':
        case '\t':
            return token_type::SPACE;
        case '$':
            return token_type::DOLLAR;
        case ':':
            return token_type::COLON;
        case '.':
            return token_type::PERIOD;
        case '[':
            return token_type::LBRAC;
        case ']':
            return token_type::RBRAC;
        case '#':
            return token_type::HASH;
        case '*':
            return token_type::STAR;
        case '-':
            return token_type::DASH;
        case '=':
            return token_type::EQUALS;
        case '<':
            return token_type::LT;
        case '>':
            return token_type::GT;
        case '|':
            return token_type::PIPE;
        case '`':
            return token_type::TICK;
        case '\\':
            return token_type::ESCAPE;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return token_type::NUMBER;
        default:
            return token_type::OTHER;
    }
}

}  // namespace sparkdown
