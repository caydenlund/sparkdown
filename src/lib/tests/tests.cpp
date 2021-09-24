
#include <string>
#include <iostream>

#include "parser.hpp"

void assert_equal(std::string expected, std::string actual, std::string test)
{
    if (expected != actual)
    {
        std::cerr << std::endl << "==================" << std::endl;
        std::cerr << test << ":\nExpected:\n" << expected << "\nbut got:\n" << actual << std::endl;
        std::cerr << "==================" << std::endl;
        exit(1);
    }
}

int main()
{
    Parser parser = Parser();

    assert_equal("12345\n", parser.parse_line("12345\n"), "Unchanged pass-through");

    assert_equal("12\\textbf{34}5\n", parser.parse_line("12**34**5\n"), "Bold text 1");
    assert_equal("1\\textbf{2}3\\textbf{4}5\n", parser.parse_line("1**2**3**4**5\n"), "Bold text 2");

    assert_equal("12\\textit{34}5\n", parser.parse_line("12*34*5\n"), "Italic text 1");
    assert_equal("1\\textit{2}3\\textit{4}5\n", parser.parse_line("1*2*3*4*5\n"), "Italic text 2");

    assert_equal("\\textbf{\\textit{12345}}", parser.parse_line("***12345***"), "Bold and italic text");

    assert_equal("\\begin{itemize}\n    \\item 12345\n", parser.parse_line("* 12345\n"), "Itemize 1");
    assert_equal("    \\item 12345\n", parser.parse_line("* 12345\n"), "Itemize 2");
    assert_equal("    \\begin{itemize}\n        \\item 12345\n", parser.parse_line("  * 12345\n"), "Itemize 3");
    assert_equal("        \\item 12345\n", parser.parse_line("  * 12345\n"), "Itemize 4");
    assert_equal("    \\end{itemize}\n    \\item 12345\n", parser.parse_line("* 12345\n"), "Itemize 5");

    assert_equal("\\end{itemize}\n12345\n", parser.parse_line("12345\n"), "Indentation");

    assert_equal("$\\rightarrow$", parser.parse_line("->"), "Arrow 1");
    assert_equal("$\\rightarrow$", parser.parse_line("-->"), "Arrow 2");
    assert_equal("$\\rightarrow$", parser.parse_line("=>"), "Arrow 3");
    assert_equal("$\\rightarrow$", parser.parse_line("==>"), "Arrow 4");
    assert_equal("$\\rightarrow$", parser.parse_line("$=>$"), "Arrow 5");
    assert_equal("$$$\\rightarrow$", parser.parse_line("$$->"), "Arrow 6");
    assert_equal("$$$\\rightarrow$", parser.parse_line("$$$->$"), "Arrow 7");
    
    assert_equal("\\section*{Section}", parser.parse_line("# Section"), "Section 1");
    assert_equal("\\subsection*{Section}", parser.parse_line("## Section"), "Section 2");
    assert_equal("\\subsubsection*{Section}", parser.parse_line("### Section"), "Section 3");

    assert_equal("\\begin{itemize}\n    \\item Bullet point with \\textit{italic text.}", parser.parse_line("* Bullet point with *italic text.*"), "Bullet point with italics");
    parser.parse_line("End itemize.");
    assert_equal("\\begin{itemize}\n    \\item Bullet point with \\textbf{bold text.}", parser.parse_line("* Bullet point with **bold text.**"), "Bullet point with bold");
    parser.parse_line("End itemize.");

    assert_equal("\\begin{itemize}\n    \\item Bullet point with $\\rightarrow$", parser.parse_line("* Bullet point with =>"), "Bullet point with right arrow.");
    parser.parse_line("End itemize.");

    assert_equal("Line with \\verb|verbatim text|.\\n", parser.parse_line("Line with |verbatim text|.\\n"), "Inline verbatim text 1");
    assert_equal("Line \\verb|with| verbatim \\verb|text|.\\n", parser.parse_line("Line |with| verbatim |text|.\\n"), "Inline verbatim text 2");

    assert_equal("\\begin{itemize}\n    \\item Bullet point with \\verb|verbatim text|.\n", parser.parse_line("* Bullet point with |verbatim text|.\n"), "Bullet point with verbatim text");
    parser.parse_line("End itemize.");

    assert_equal("\\begin{verbatim}\n", parser.parse_line("```\n"), "Start verbatim");
    assert_equal("*Italics* unevaluated.\n", parser.parse_line("*Italics* unevaluated.\n"), "Verbatim italics");
    assert_equal("   Spacing preserved.\n", parser.parse_line("   Spacing preserved.\n"), "Verbatim indentation");
    assert_equal("\\end{verbatim}\n", parser.parse_line("```\n"), "End verbatim");

    return 0;
}