// src/sidebars.ts
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/18/2021
//
// This file is part of Sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the configuration
// for the Docusaurus documentation sidebars.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

const sidebars = {
    "getting-started": [
        "getting-started/intro",
        "getting-started/building",
        "getting-started/simple-example",
        "getting-started/advanced-example",
        "getting-started/unit-testing",
        "getting-started/what-next"
    ],
    docs: [
        "intro",
        "installation",
        "cli",
        {
            type: "category",
            label: "API",
            items: ["api/state", "api/lexer"]
        },
        {
            type: "category",
            label: "Sparkdown Features",
            items: [
                "features/header",
                "features/section",
                "features/lists",
                "features/arrow",
                "features/bold-italics",
                "features/math",
                "features/verbatim"
            ]
        }
    ]
};

module.exports = sidebars;
