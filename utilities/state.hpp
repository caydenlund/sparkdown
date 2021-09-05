#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <regex>
#include <stack>

// A class to represent the state of the parser.
class State
{
public:
    State();
    std::string indent();
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
    std::string preline;
    std::string line;
    void increase_itemize();
    void decrease_itemize();
    void increase_enumerate();
    void decrease_enumerate();
};

// Constructor.
State::State()
{
    indentation = 0;
    preline = "";
    line = "";
}

// Returns a string of spaces to indent the next line.
std::string State::indent()
{
    std::string result;
    for (int i = 0; i < indentation; i++)
    {
        result += "    ";
    }
    return result;
}

// Sets the indentation to the given value.
void State::set_indentation(int indentation)
{
    while (this->indentation > indentation)
    {
        if (levels.top() == itemize)
        {
            decrease_itemize();
        }
        else
        {
            decrease_enumerate();
        }
    }
}

// Sets the idemization level to itemize.
void State::begin_itemize(int level)
{
    while (levels.size() > level)
    {
        if (levels.top() == itemize)
        {
            decrease_itemize();
        }
        else
        {
            decrease_enumerate();
        }
    }
    while (levels.size() < level)
    {
        increase_itemize();
    }
    if (level > 0 && levels.top() != itemize)
    {
        decrease_enumerate();
        increase_itemize();
    }
}

void State::begin_enumerate(int level)
{
    while (levels.size() > level)
    {
        if (levels.top() == itemize)
        {
            decrease_itemize();
        }
        else
        {
            decrease_enumerate();
        }
    }
    while (levels.size() < level)
    {
        increase_enumerate();
    }
    if (level > 0 && levels.top() != enumerate)
    {
        decrease_itemize();
        increase_enumerate();
    }
}

// Returns the current line.
std::string State::get_line()
{
    return line;
}

// Sets the current line.
void State::set_line(std::string line)
{
    this->line = line;
}

// Returns the final product.
std::string State::get_product()
{
    std::string product = preline + indent() + line;
    preline = "";
    line = "";
    return product;
}

// Increases the itemize level.
void State::increase_itemize()
{
    preline += indent() + "\\begin{itemize}\n";
    levels.push(itemize);
    indentation++;
}

// Decreases the itemize level.
void State::decrease_itemize()
{
    indentation--;
    preline += indent() + "\\end{itemize}\n";
    if (levels.top() != itemize) {
        throw std::runtime_error("Itemize level mismatch.");
        exit(1);
    }
    levels.pop();
}

// Increases the enumerate level.
void State::increase_enumerate()
{
    preline += indent() + "\\begin{enumerate}\n";
    levels.push(enumerate);
    indentation++;
}

// Decreases the enumerate level.
void State::decrease_enumerate()
{
    indentation--;
    preline += indent() + "\\end{enumerate}\n";
    if (levels.top() != enumerate) {
        throw std::runtime_error("Enumerate level mismatch.");
        exit(1);
    }
    levels.pop();
}

#endif