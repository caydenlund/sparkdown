/**
 * @file parser/patterns/pattern.hpp
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `pattern` class definition.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file defines the `pattern` class,
 *     which serves as the base class for all pattern-matching rules
 *     for the parser.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <list>
#include <string>

#include "state/state.hpp"
#include "token/token.hpp"

namespace sparkdown {

typedef std::list<token> token_list;

/**
 * @brief Base class for any pattern rules for the parser.
 *
 */
class pattern {
   protected:
    /**
     * @brief Pointer to the parser's state object.
     *
     */
    state *_state;

   public:
    /**
     * @brief Zero-argument constructor.
     *
     */
    pattern() : _state(nullptr) {}

    /**
     * @brief Updates the pointer to the parser's state object
     *     to the given value.
     *
     * @param state The pointer to the state object.
     */
    void set_state(state *s) { this->_state = s; }

    /**
     * @brief Reports whether this pattern is usable in the current state.
     * @details Pure virtual function.
     *
     * @return True if this pattern is usable in the current state.
     */
    [[nodiscard]] virtual bool usable() const = 0;

    /**
     * @brief Resets this pattern to its initial state.
     * @details Used when parsing a new line.
     *
     */
    virtual void reset() = 0;

    /**
     * @brief Attempts to match the pattern at the specified iterator location.
     * @details If the pattern matches, the entries in the vector are replaced
     *     with the corresponding complex token.
     *
     * @param tokens The list of tokens to scan.
     * @param position The position of the token to try to match.
     */
    virtual token_list::iterator match(token_list &tokens,
                                       token_list::iterator position) = 0;
};

}  // namespace sparkdown

#endif
#pragma clang diagnostic pop