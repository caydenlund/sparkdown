// //state
// v. 0.6.2
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the implementation of the State class.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#include <string>
#include <regex>
#include <stack>

// The header file for the State class.
#include "state.hpp"

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // Constructor.
    State::State()
    {
        this->indentation = 0;

        this->verbatim = false;
        this->math = false;

        this->head = true;
    }

    // Returns true if we are looking at the head of the document.
    //
    // * return bool - True if we are looking at the head of the document.
    bool State::is_head()
    {
        return this->head;
    }

    // Ends the head of the document.
    void State::end_head()
    {
        this->head = false;
    }

    // Returns true if verbatim mode is on.
    //
    // * return bool - True if verbatim mode is on.
    bool State::is_verbatim()
    {
        return this->verbatim;
    }

    // Toggles verbatim mode.
    void State::toggle_verbatim()
    {
        this->verbatim = !this->verbatim;
    }

    // Returns true if math mode is on.
    //
    // * return bool - True if math mode is on.
    bool State::is_math()
    {
        return this->math;
    }

    // Toggles math mode.
    void State::toggle_math()
    {
        this->math = !this->math;
    }

    // Returns a string of spaces to indent the next line.
    //
    // * return std::string - A string of spaces to indent the next line.
    std::string State::indent()
    {
        std::stringstream result;
        for (int i = 0; i < this->indentation; i++)
        {
            result << " ";
        }
        return result.str();
    }

    // Decreases the list level to the given value.
    //
    // * int list level - The new list level.
    void State::decrease_list_level(int level)
    {
        while (this->levels.size() > (long unsigned int)level)
        {
            this->indentation -= 4;
            this->levels.pop();
        }
    }

    // Returns the current list level.
    //
    // * return int - The current list level.
    int State::get_list_level()
    {
        return this->levels.size();
    }

    // Returns the current list type.
    //
    // * return State::level_type - The current list type.
    State::level_type State::get_list_type()
    {
        if (this->levels.empty())
            throw std::runtime_error("No list level.");
        return this->levels.top();
    }

    // Begins a new list of the given type.
    //
    // * int level       - The new list level.
    // * level_type type - The type of list.
    void State::begin_list(int level, level_type type)
    {
        this->decrease_list_level(level - 1);
        while (this->levels.size() < (long unsigned int)level)
        {
            this->indentation += 4;
            this->levels.push(type);
        }
    }
}
