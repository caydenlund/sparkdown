/**
 * @file parser/parser.hpp
 * @package //parser:parser
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `parser` class definition and implementation.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file defines and implements the `parser` class,
 *     which is used to parse a sequence of tokens into
 *     a model of syntactic meaning.
 *
 *     Note that this file contains both the definition and the implementation,
 *     because the C++ standard requires that templated method implementations
 *     be done in the header file.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <tuple>

#include "patterns/pattern.hpp"
#include "state/state.hpp"

namespace sparkdown {

/**
 * @brief Parses a sequence of tokens into a model of syntactic meaning.
 *
 */
template <class... pattern_list>
class parser {
   private:
    /**
     * @brief Holds information about the state of the parser.
     *
     */
    state _state;

    /**
     * @brief The list of patterns to use, ordered by execution order.
     *
     */
    std::tuple<pattern_list...> _patterns;

    template <class P>
    void _apply_pattern(P &p, token_list &tokens,
                        token_list::iterator &position) {
        if (p.usable()) {
            position = p.match(tokens, position);
        }
    }

   public:
    /**
     * @brief Constructor.
     *
     */
    parser() {
        std::apply([this](auto &...p) { ((p.set_state(&this->_state)), ...); },
                   _patterns);
    }

    /**
     * @brief Parses the given sequence of tokens.
     * @details Note that it operates in-place on the input list.
     *     (I.e., it changes the input list directly,
     *     and nothing is returned.)
     *
     * @param tokens The sequence of tokens to parse.
     */
    void parse(token_list &tokens) {
        for (auto position = tokens.begin(); position != tokens.end();
             position++) {
            std::apply(
                [&](auto &...p) {
                    ((this->_apply_pattern(p, tokens, position)), ...);
                },
                _patterns);
        }
    }
};

}  // namespace sparkdown

#endif