/**
 * @file token/token.cpp
 * @package //token:token
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `token` class implementation.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file implements the `token` class,
 *     which represents a single token in the lexing/parsing process.
 *
 *     See the header file for documentation.
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
            return token_type::CHAR_SPACE;
        case '$':
            return token_type::CHAR_DOLLAR;
        case ':':
            return token_type::CHAR_COLON;
        case '.':
            return token_type::CHAR_PERIOD;
        case '[':
            return token_type::CHAR_LBRAC;
        case ']':
            return token_type::CHAR_RBRAC;
        case '#':
            return token_type::CHAR_HASH;
        case '*':
            return token_type::CHAR_STAR;
        case '-':
            return token_type::CHAR_DASH;
        case '=':
            return token_type::CHAR_EQUALS;
        case '<':
            return token_type::CHAR_LT;
        case '>':
            return token_type::CHAR_GT;
        case '|':
            return token_type::CHAR_PIPE;
        case '`':
            return token_type::CHAR_TICK;
        case '\\':
            return token_type::CHAR_ESCAPE;
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
            return token_type::CHAR_NUMBER;
        default:
            return token_type::CHAR_OTHER;
    }
}

}  // namespace sparkdown
