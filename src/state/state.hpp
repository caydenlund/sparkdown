// //state
// v. 0.6.2
//
// Author: Cayden Lund
//   Date: 10/27/2021
//
// This file is part of sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the State class headers.
// See state.cpp for implementation.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <stack>

// The sparkdown namespace contains all the classes and methods of the sparkdown library.
namespace sparkdown
{
    // A class to represent the state of the parser.
    class State
    {
    public:
        // Constructor.
        State();

        // An enum to represent a type of list.
        enum level_type
        {
            itemize,
            enumerate
        };

        // Returns true if we are looking at the head of the document.
        //
        // * return bool - True if we are looking at the head of the document.
        bool is_head();

        // Set `head` to false.
        void end_head();

        // Returns true if verbatim mode is on.
        bool is_verbatim();

        // Toggles verbatim mode.
        void toggle_verbatim();

        // Returns true if math mode is on.
        bool is_math();

        // Toggles math mode.
        void toggle_math();

        // Returns a string of spaces to indent the next line.
        std::string indent();

        // Decreases the list level to the given value.
        //
        // * int level - The new list level.
        void decrease_list_level(int level);

        // Returns the current list level.
        int get_list_level();

        // Returns the current list type.
        level_type get_list_type();

        // Begins a new list of the given type.
        //
        // * int level       - The new list level.
        // * level_type type - The type of list.
        void begin_list(int level, level_type type);

    private:
        // =======================
        // | Instance variables. |
        // =======================

        // The number of spaces to indent the next line.
        int indentation;

        // A stack to represent the current itemize/enumerate level.
        std::stack<level_type> levels;

        // Whether or not we are in verbatim mode.
        bool verbatim;

        // Whether or not we are in math mode.
        bool math;

        // Whether or not we are in the head of the document.
        bool head;
    };
}

#endif