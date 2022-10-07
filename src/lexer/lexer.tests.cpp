/**
 * @file lexer/lexer.tests.cpp
 * @package //lexer:lexer.tests
 * @author Cayden Lund <cayden.lund@utah.edu>
 * @brief `lexer` class unit tests.
 * @details This project is part of Sparkdown,
 *     a new markup language for quickly writing and formatting notes.
 *
 *     This file tests the `lexer` class,
 *     which is used to lex a string into a sequence of tokens.
 *
 * @license MIT <https://opensource.org/licenses/MIT>
 * @copyright 2021-2022 by Cayden Lund <https://github.com/caydenlund>
 */

#include "lexer.hpp"

#include <gtest/gtest.h>

#include "token/token.hpp"

/**
 * @brief Ensures that the lexer returns an empty list
 *     when given an empty string.
 *
 */
TEST(lexer, handles_empty_string) {
    sparkdown::lexer lexer;
    std::list<sparkdown::token> tokens;
    EXPECT_TRUE(tokens.empty());

    lexer.lex("");
    tokens = lexer.get_tokens();
    EXPECT_TRUE(tokens.empty());
}

/**
 * @brief Ensures that the lexer correctly lexes a simple string.
 *
 */
TEST(lexer, handles_simple_string) {
    sparkdown::lexer lexer;
    std::list<sparkdown::token> tokens_list;
    std::vector<sparkdown::token> tokens_vec;

    lexer.lex("abc");

    tokens_list = lexer.get_tokens();
    for (sparkdown::token &token : tokens_list) {
        tokens_vec.push_back(token);
    }

    EXPECT_EQ(tokens_vec.size(), 3);
    EXPECT_EQ(tokens_vec[0].type, sparkdown::token_type::CHAR_OTHER);
    EXPECT_EQ(tokens_vec[0].value, 'a');
    EXPECT_EQ(tokens_vec[1].type, sparkdown::token_type::CHAR_OTHER);
    EXPECT_EQ(tokens_vec[1].value, 'b');
    EXPECT_EQ(tokens_vec[2].type, sparkdown::token_type::CHAR_OTHER);
    EXPECT_EQ(tokens_vec[2].value, 'c');
}

/**
 * @brief Ensures that the lexer correctly flushes the buffer
 *     when `lexer#get_tokens()` is called.
 *
 */
TEST(lexer, flushes_buffer) {
    sparkdown::lexer lexer;
    std::list<sparkdown::token> tokens;

    lexer.lex("abc");
    tokens = lexer.get_tokens();
    EXPECT_EQ(tokens.size(), 3);

    tokens = lexer.get_tokens();
    EXPECT_EQ(tokens.size(), 0);
}

/**
 * @brief Ensures that the lexer can be reused after the buffer
 *     has been flushed at least once.
 *
 */
TEST(lexer, is_reusable) {
    sparkdown::lexer lexer;
    std::list<sparkdown::token> tokens_list;
    std::vector<sparkdown::token> tokens_vec;

    lexer.lex("abc");

    tokens_list = lexer.get_tokens();
    for (sparkdown::token &token : tokens_list) {
        tokens_vec.push_back(token);
    }

    EXPECT_EQ(tokens_vec.size(), 3);

    tokens_list = lexer.get_tokens();

    EXPECT_EQ(tokens_list.size(), 0);

    lexer.lex("123");

    tokens_list = lexer.get_tokens();
    tokens_vec.clear();
    for (sparkdown::token &token : tokens_list) {
        tokens_vec.push_back(token);
    }

    EXPECT_EQ(tokens_vec[0].type, sparkdown::token_type::CHAR_NUMBER);
    EXPECT_EQ(tokens_vec[0].value, '1');
    EXPECT_EQ(tokens_vec[1].type, sparkdown::token_type::CHAR_NUMBER);
    EXPECT_EQ(tokens_vec[1].value, '2');
    EXPECT_EQ(tokens_vec[2].type, sparkdown::token_type::CHAR_NUMBER);
    EXPECT_EQ(tokens_vec[2].value, '3');
}
