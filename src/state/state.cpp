/**
 * @file state/state.cpp
 * @package //state:state
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `state` class implementation.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file implements the `state` class,
 *     which represents the state of the language parser.
 *
 *     See the header file for documentation.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#include "state.hpp"

namespace sparkdown {

state::state() : _is_head(true), _is_math(false), _is_verbatim(false) {}

void state::end_head() { this->_is_head = false; }

bool state::is_head() const { return this->_is_head; }

void state::toggle_is_math() { this->_is_math = !this->_is_math; }

bool state::is_math() const { return this->_is_math; }

void state::toggle_is_verbatim() { this->_is_verbatim = !this->_is_verbatim; }

bool state::is_verbatim() const { return this->_is_verbatim; }

}  // namespace sparkdown
