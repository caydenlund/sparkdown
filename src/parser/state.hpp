// src/parser/state.hpp
// v. 0.4.0
//
// Author: Cayden Lund
//   Date: 10/05/2021
//
// This file is part of mark-sideways, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the State class.
// See state.cc for implementation and documentation.
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
        State();
        std::string indent();
        bool is_verbatim();
        std::string toggle_verbatim();
        void set_indentation(int indentation);
        void begin_itemize(int level);
        void begin_enumerate(int level);
        std::string get_line();
        void set_line(std::string line);
        std::string get_product();

    protected:
        enum level_type
        {
            itemize,
            enumerate
        };
        std::stack<level_type> levels;
        int indentation;
        bool verbatim;
        std::string preline;
        std::string line;
        void increase_itemize();
        void decrease_itemize();
        void increase_enumerate();
        void decrease_enumerate();
    };
}

#endif