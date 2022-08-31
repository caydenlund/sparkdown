/**
 * @file token/token.hpp
 * @package //token:token
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `token` class definition.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file defines the `token` class,
 *     which represents a single token in the lexing/parsing process.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace sparkdown {

/**
 * @brief An enumeration of the possible token types.
 *
 */
enum token_type {
    SPACE,   // A space.              [ \t]
    DOLLAR,  // A dollar sign.        '$'
    COLON,   // A colon.              ':'
    PERIOD,  // A period.             '.'
    LBRAC,   // A left bracket.       '['
    RBRAC,   // A right bracket.      ']'
    HASH,    // A hash.               '#'
    STAR,    // An asterisk.          '*'
    DASH,    // A hyphen.             '-'
    EQUALS,  // An equals sign.       '='
    LT,      // A less-than sign.     '<'
    GT,      // A greater-than sign.  '>'
    PIPE,    // A vertical bar.       '|'
    TICK,    // A backtick.           '`'
    ESCAPE,  // A backslash.          '\'
    NUMBER,  // A numeral.            [0-9]+
    OTHER    // Anything else.
};

/**
 * @brief Represents a single character in a string of Sparkdown text.
 * @details The lexer will create a list of tokens from a string.
 *     These tokens are then used by the parser to parse the sequence of tokens
 *     into LaTeX code.
 *
 */
struct token {
    /**
     * @brief Constructs a new token from a single character.
     * @details The implicit construction is intentional.
     *
     * @param character The character used to construct the token.
     */
    token(char character);

    /**
     * @brief Copy constructor.
     *
     * @param other The other token to copy.
     */
    token(const token &other);

    /**
     * @brief Equality comparison operator.
     *
     * @param other The other token to compare with this one.
     * @return Whether the tokens are equal.
     */
    bool operator==(const token &other) const;

    /**
     * @brief Inequality comparison operator.
     *
     * @param other The other token to compare with this one.
     * @return Whether the tokens are unequal.
     */
    bool operator!=(const token &other) const;

    /**
     * @brief Given a character, returns the corresponding token type.
     *
     * @param character The character to test.
     * @return The corresponding token type.
     */
    static token_type get_type(char character);

    /**
     * @brief The type of the token.
     *
     */
    const token_type type;

    /**
     * @brief The value of the token.
     *
     */
    const char value;
};
}  // namespace sparkdown

#endif