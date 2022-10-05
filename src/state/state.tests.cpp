/**
 * @file state/state.tests.cpp
 * @package //state:state.tests
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `state` class unit tests.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file tests the `state` class,
 *     which represents the state of the language parser.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "UnusedLocalVariable"

#include "state.hpp"

#include <gtest/gtest.h>

/**
 * @brief `state#state()` no-fail test.
 * @details Ensures that the constructor does not throw an exception.
 *
 */
TEST(state, constructor_no_fail) { sparkdown::state s; }

/**
 * @brief `state#is_head()` test.
 *
 */
TEST(state, is_head) {
    sparkdown::state s;
    EXPECT_TRUE(s.is_head());

    s.end_head();
    EXPECT_FALSE(s.is_head());
}

/**
 * @brief `state#is_math()` test.
 *
 */
TEST(state, is_math) {
    sparkdown::state s;
    EXPECT_FALSE(s.is_math());

    s.toggle_is_math();
    EXPECT_TRUE(s.is_math());

    s.toggle_is_math();
    EXPECT_FALSE(s.is_math());
}

/**
 * @brief `state#is_verbatim()` test.
 *
 */
TEST(state, is_verbatim) {
    sparkdown::state s;
    EXPECT_FALSE(s.is_verbatim());

    s.toggle_is_verbatim();
    EXPECT_TRUE(s.is_verbatim());

    s.toggle_is_verbatim();
    EXPECT_FALSE(s.is_verbatim());
}

#pragma clang diagnostic pop
