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
 * @details
 *
 *     Tokens referring to a single character are prefixed with `CHAR_`.
 *
 *     Complex tokens are prefixed with `COMP_`.
 *     These tokens are not generated by the lexer,
 *     but instead are generated by the parser.
 *
 */
enum token_type {
    // //======================\\
    // ||  Single Characters:  ||
    // \\======================//

    CHAR_SPACE,   // A space.              [ \t]
    CHAR_DOLLAR,  // A dollar sign.        '$'
    CHAR_COLON,   // A colon.              ':'
    CHAR_PERIOD,  // A period.             '.'
    CHAR_LBRAC,   // A left bracket.       '['
    CHAR_RBRAC,   // A right bracket.      ']'
    CHAR_HASH,    // A hash.               '#'
    CHAR_STAR,    // An asterisk.          '*'
    CHAR_DASH,    // A hyphen.             '-'
    CHAR_EQUALS,  // An equals sign.       '='
    CHAR_LT,      // A less-than sign.     '<'
    CHAR_GT,      // A greater-than sign.  '>'
    CHAR_PIPE,    // A vertical bar.       '|'
    CHAR_TICK,    // A backtick.           '`'
    CHAR_ESCAPE,  // A backslash.          '\'
    CHAR_NUMBER,  // A numeral.            [0-9]+
    CHAR_OTHER,   // Anything else.

    // //====================\\
    // ||  Compound tokens:  ||
    // \\====================//

    // Head tokens:
    // ------------
    COMP_AUTHOR,  // "$author: "
    COMP_DATE,    // "$date: "
    COMP_TITLE,   // "$title: "

    // Body tokens:
    // ------------
    COMP_R_ARROW  // "->"
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
    token(char character);  // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructs a new token from a single token type.
     * @details The implicit construction is intentional.
     *
     *     Useful for the complex tokens.
     *
     * @param type The token type used to construct the token.
     */
    token(token_type type);  // NOLINT(google-explicit-constructor)

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