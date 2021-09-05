# Mark-sideways

A new markup/markdown language for quickly taking notes.

Written from scratch in C++.

Notes are transpiled into LaTeX and can then be compiled into a PDF.

## Usage:

    Usage: mark-sideways <file> [OPTIONS]
      Options:
        -h, --help: 	    Print this help message.
        -v, --version:	    Print version information.
        -o, --output:	    Output file.
        -w, --overwrite:	Overwrite output file if it exists.

## Syntax:
    
    $title: Title
    $author: Author
    $date: Date

    =============  % Border between metadata and content.

    # Header.

    ## Sub-header.

    ### Sub-sub-header (etc.).

    % Comment.

    * List item.
      Can contain newlines for readability.
      \\ Create an actual newline.
      * Sub-list item (etc.).

      - Sub-list item.
        Line breaks for readability don't interrupt the flow
        of the bullet list.
        

    1. Ordered list item.
      1. Sub-ordered list item (etc.).

    * Bullets
      1. and numerals
      2. can be used together.

    *Italic text.*

    _Italic text._

    **Bold text.**

    -> Rightarrow.
    => Rightarrow.
    --> Rightarrow.
    ==> Rightarrow.

## Output:

![](example.png)
