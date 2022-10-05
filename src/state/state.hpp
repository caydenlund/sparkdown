/**
 * @file state/state.hpp
 * @package //state:state
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `state` class definition.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file defines the `state` class,
 *     which represents the state of the language parser.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#ifndef STATE_HPP
#define STATE_HPP

namespace sparkdown {

/**
 * @brief Represents the state of the language parser.
 *
 */
class state {
   private:
    /**
     * @brief Whether we are currently parsing the head of the document.
     *
     */
    bool _is_head;

    /**
     * @brief Whether we are currently parsing math.
     *
     */
    bool _is_math;

    /**
     * @brief Whether we are currently parsing verbatim text.
     *
     */
    bool _is_verbatim;

   public:
    /**
     * @brief Constructor.
     *
     */
    state();

    /**
     * @brief Indicates to the state that the language parser is no longer
     *     parsing the head of the document.
     *
     */
    void end_head();

    /**
     * @brief Reports whether we are currently parsing the head of the document.
     *
     * @return True if we are currently parsing the head of the document.
     */
    bool is_head() const;

    /**
     * @brief Toggles whether we are currently parsing math.
     *
     */
    void toggle_is_math();

    /**
     * @brief Reports whether we are currently parsing math.
     *
     * @return True if we are currently parsing math.
     */
    bool is_math() const;

    /**
     * @brief Toggles whether we are currently parsing verbatim text.
     *
     */
    void toggle_is_verbatim();

    /**
     * @brief Reports whether we are currently parsing verbatim text.
     *
     * @return True if we are currently parsing verbatim text.
     */
    bool is_verbatim() const;
};

}  // namespace sparkdown

#endif