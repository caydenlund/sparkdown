/**
 * @file parser/parser.tests.cpp
 * @package //parser:parser.tests
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `parser` class unit tests.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file tests the `parser` class,
 *     which represents the parser of the language parser.
 *
 *     Note that the tests contained in this file are not testing the individual
 *     patterns of the language; they just test the correctness of the parser.
 *     Each pattern has its own file of test definitions in the
 *     `//parser/patterns` directory.
 *
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "UnusedLocalVariable"

#include "parser/parser.hpp"

#include <gtest/gtest.h>

#include <list>

/**
 * @brief Dummy pattern class for testing. (1/5)
 * @details It is always usable, and never changes the token sequence.
 *
 */
class dummy_pattern_1 : public sparkdown::pattern {
   public:
    [[nodiscard]] bool usable() const override { return true; }

    void reset() override {}

    sparkdown::token_list::iterator match(
        sparkdown::token_list &tokens,
        sparkdown::token_list::iterator position) override {
        return position;
    }
};

/**
 * @brief Dummy pattern class for testing. (2/5)
 * @details It is never usable,
 *     and always changes the token sequence if used anyway.
 *
 */
class dummy_pattern_2 : public sparkdown::pattern {
   public:
    /**
     * @brief Always returns false (i.e., should never be used).
     *
     * @return False.
     */
    [[nodiscard]] bool usable() const override { return false; }

    void reset() override {}

    /**
     * @brief Replaces the current token with an '='.
     *
     * @param tokens The list of tokens.
     * @param position The current position in the list.
     * @return The new position in the list.
     */
    sparkdown::token_list::iterator match(
        sparkdown::token_list &tokens,
        sparkdown::token_list::iterator position) override {
        position = tokens.erase(position);
        return tokens.insert(position, '=');
    }
};

/**
 * @brief Dummy pattern class for testing. (3/5)
 * @details Uses the parser's state when determining whether it can be used,
 *     and changes the token sequence when a match is found.
 *
 */
class dummy_pattern_3 : public sparkdown::pattern {
   public:
    /**
     * @brief Returns true if we are not in math mode.
     *
     * @return True if we are not in math mode.
     */
    [[nodiscard]] bool usable() const override {
        return !this->_state->is_math();
    }

    void reset() override {}

    /**
     * @brief Upon encountering a '2', replaces the '2' with a '#'.
     *
     * @param tokens The list of tokens to view and modify.
     * @param position The position of the iterator within the list of tokens.
     * @return The new position of the iterator.
     */
    sparkdown::token_list::iterator match(
        sparkdown::token_list &tokens,
        sparkdown::token_list::iterator position) override {
        if (position->type == sparkdown::token_type::CHAR_NUMBER &&
            position->value == '2') {
            position = tokens.erase(position);
            return tokens.insert(position, '#');
        }

        return position;
    }
};

/**
 * @brief Dummy pattern class for testing. (4/5)
 * @details Uses the parser's state when determining whether it can be used,
 *     and changes the token sequence when a match is found.
 *
 */
class dummy_pattern_4 : public sparkdown::pattern {
   public:
    /**
     * @brief Returns true when the parser is in math mode.
     *
     * @return True when the parser is in math mode.
     */
    [[nodiscard]] bool usable() const override {
        return this->_state->is_math();
    }

    void reset() override {}

    sparkdown::token_list::iterator match(
        sparkdown::token_list &tokens,
        sparkdown::token_list::iterator position) override {
        if (position != tokens.end() &&
            position->type == sparkdown::token_type::CHAR_DASH) {
            auto next = position;
            next++;

            if (next->type == sparkdown::token_type::CHAR_GT) {
                position = tokens.erase(position, ++next);
                return tokens.insert(position,
                                     sparkdown::token_type::COMP_R_ARROW);
            }
        }

        return position;
    }
};

/**
 * @brief Dummy pattern class for testing. (5/5)
 * @details Does not make changes; rather, it just toggles whether
 *     the parser is in math mode upon seeing a '$'.
 *
 */
class dummy_pattern_5 : public sparkdown::pattern {
   public:
    /**
     * @brief Always returns true (i.e., it should always be used).
     *
     * @return True.
     */
    [[nodiscard]] bool usable() const override { return true; }

    void reset() override {}

    /**
     * @brief If the current token is a '$', updates the state accordingly.
     *
     * @param tokens The list of tokens.
     * @param position The current position in the list.
     * @return The new position in the list.
     */
    sparkdown::token_list::iterator match(
        sparkdown::token_list &tokens,
        sparkdown::token_list::iterator position) override {
        if (position->type == sparkdown::token_type::CHAR_DOLLAR) {
            this->_state->toggle_is_math();
        }

        return position;
    }
};

/**
 * @brief `parser#parser()` no-fail test.
 * @details Ensures that the constructor does not throw an exception.
 *
 */
TEST(parser, constructor_no_fail) {
    // Test various arrangements of pattern matchers:
    sparkdown::parser<> parser_1;
    sparkdown::parser<dummy_pattern_1> parser_2;
    sparkdown::parser<dummy_pattern_1, dummy_pattern_2> parser_3;
    sparkdown::parser<dummy_pattern_1, dummy_pattern_2, dummy_pattern_3>
        parser_4;
    sparkdown::parser<dummy_pattern_1, dummy_pattern_2, dummy_pattern_3,
                      dummy_pattern_4>
        parser_5;
    sparkdown::parser<dummy_pattern_1, dummy_pattern_2, dummy_pattern_3,
                      dummy_pattern_3>
        parser_6;
}

/**
 * @brief `parser#parse()` no-change test.
 * @details Ensures that the parser does not change the input sequence
 *     when none of the pattern-matching classes apply.
 *
 */
TEST(parser, parse_no_change) {
    sparkdown::token_list input;
    sparkdown::token_list expected = {'a', 'b', 'c'};

    // Parser 1: no pattern.
    input = sparkdown::token_list(expected);
    sparkdown::parser<> parser_1;
    parser_1.parse(input);
    EXPECT_EQ(input, expected);

    // Parser 2: non-modifying pattern.
    input = sparkdown::token_list(expected);
    sparkdown::parser<dummy_pattern_1> parser_2;
    parser_2.parse(input);
    EXPECT_EQ(input, expected);

    // Parser 3: unusable pattern.
    input = sparkdown::token_list(expected);
    sparkdown::parser<dummy_pattern_2> parser_3;
    parser_3.parse(input);
    EXPECT_EQ(input, expected);

    // Parser 4: non-modifying pattern before unusable pattern.
    input = sparkdown::token_list(expected);
    sparkdown::parser<dummy_pattern_1, dummy_pattern_2> parser_4;
    parser_4.parse(input);
    EXPECT_EQ(input, expected);

    // Parser 5: unusable pattern before non-modifying pattern.
    input = sparkdown::token_list(expected);
    sparkdown::parser<dummy_pattern_2, dummy_pattern_1> parser_5;
    parser_5.parse(input);
    EXPECT_EQ(input, expected);
}

/**
 * @brief `parser#parse()` change test.
 * @details Ensures that the parser correctly changes the input token list
 *     when appropriate.
 *
 */
TEST(parser, parse_change) {
    sparkdown::token_list input;
    sparkdown::token_list expected;

    // Parser 1: replaces all occurrences of '2' with '#' outside of math mode.
    input = sparkdown::token_list({'a', 'b', 'c', '1', '2', '3'});
    expected = sparkdown::token_list({'a', 'b', 'c', '1', '#', '3'});
    sparkdown::parser<dummy_pattern_3> parser_1;
    parser_1.parse(input);
    EXPECT_EQ(input, expected);

    // Parser 2: replaces all occurrences of "->" with COMP_R_ARROW
    //           inside math mode.
    input = sparkdown::token_list({'a', '$', '-', '>', '$', '3'});
    expected = sparkdown::token_list(
        {'a', '$', sparkdown::token_type::COMP_R_ARROW, '$', '3'});
    sparkdown::parser<dummy_pattern_4, dummy_pattern_5> parser_2;
    parser_2.parse(input);
    EXPECT_EQ(input, expected);
}

#pragma clang diagnostic pop