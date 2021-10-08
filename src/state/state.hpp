// src/state/state.hpp
// v. 0.5.1
//
// Author: Cayden Lund
//   Date: 10/07/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the State class headers.
// See state.cpp for implementation.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT (https://opensource.org/licenses/MIT)

#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <stack>

// The mark_sideways namespace contains all the classes and methods of the mark-sideways library.
namespace mark_sideways
{
    // A class to represent the state of the parser.
    class State
    {
    public:
        // Constructor.
        State();

        // Returns a string of spaces to indent the next line.
        std::string indent();

        // Returns true if verbatim mode is on.
        bool is_verbatim();

        // Returns the necessary \begin{verbatim} or \end{verbatim} commands.
        std::string toggle_verbatim();

        // Returns true if math mode is on.
        bool is_math();

        // Toggles math mode.
        void toggle_math();

        // Sets the indentation to the given value.
        //
        // * int indentation - The new identation level.
        void set_indentation(int indentation);

        // Sets the idemization level to itemize.
        //
        // * int level - The new idemization level.
        void begin_itemize(int level);

        // Sets the enumeration level to enumerate.
        //
        // * int level - The new enumeration level.
        void begin_enumerate(int level);

        // Returns the current line.
        std::string get_line();

        // Sets the current line.
        //
        // * std::string line - The new current line.
        void set_line(std::string line);

        // Returns the final product.
        std::string get_product();

    protected:
        // ====================
        // | Private methods. |
        // ====================

        // Adds the necessary \begin{itemize} command and increments the itemize level.
        void increase_itemize();

        // Adds the necessary \end{itemize} command and decrements the itemize level.
        void decrease_itemize();

        // Adds the necessary \begin{enumerate} command and increments the enumeration level.
        void increase_enumerate();

        // Adds the necessary \end{enumerate} command and decrements the enumeration level.
        void decrease_enumerate();

        // =======================
        // | Instance variables. |
        // =======================

        // An enum to represent what type of list we are in.
        enum level_type
        {
            itemize,
            enumerate
        };

        // A stack to represent the current itemize/enumerate level.
        std::stack<level_type> levels;

        // The current indentation level.
        int indentation;

        // Whether or not we are in verbatim mode.
        bool verbatim;

        // Whether or not we are in math mode.
        bool math;

        // The text preceding the line we are currently parsing.
        std::string preline;

        // The current line.
        std::string line;
    };
}

#endif