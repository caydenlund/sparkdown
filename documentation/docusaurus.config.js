// docusaurus.config.js
// v. 0.1.0
//
// Authors: Cayden Lund
//          Facebook - Docusaurus Team
//    Date: 10/18/2021
//
// This file is part of Sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the configuration
// for the Docusaurus static site generator.

// @ts-check

const lightCodeTheme = require("prism-react-renderer/themes/github");
const darkCodeTheme = require("prism-react-renderer/themes/dracula");

/** @type {import("@docusaurus/types").Config} */
const config = {
    title: "Sparkdown",
    tagline: "A new markup/markdown language for quickly taking notes.",
    url: "https://shrimpster00.github.io",
    baseUrl: "/sparkdown/",
    onBrokenLinks: "throw",
    onBrokenMarkdownLinks: "warn",
    favicon: "img/favicon/favicon.ico",
    organizationName: "shrimpster00",
    projectName: "sparkdown",

    presets: [
        [
            "@docusaurus/preset-classic",
            /** @type {import("@docusaurus/preset-classic").Options} */
            ({
                docs: {
                    sidebarPath: require.resolve("./src/sidebars.ts"),
                    editUrl:
                        "https://github.com/shrimpster00/" +
                        "sparkdown/edit/documentation/"
                },
                blog: {
                    showReadingTime: false,
                    editUrl:
                        "https://github.com/shrimpster00/" +
                        "sparkdown/edit/documentation/"
                },
                theme: {
                    customCss: require.resolve("./src/global.css")
                }
            })
        ]
    ],

    themeConfig:
        /** @type {import("@docusaurus/preset-classic").ThemeConfig} */
        ({
            navbar: {
                title: "Sparkdown",
                logo: {
                    alt: "Sparkdown Logo",
                    src: "img/logo.svg"
                },
                items: [
                    {
                        type: "doc",
                        docId: "getting-started/intro",
                        position: "left",
                        label: "Quickstart"
                    },
                    {
                        type: "doc",
                        docId: "intro",
                        position: "left",
                        label: "Documentation"
                    },
                    {to: "/blog", label: "Blog", position: "left"},
                    {
                        href: "https://github.com/shrimpster00/sparkdown",
                        label: "GitHub",
                        position: "right"
                    }
                ]
            },
            footer: {
                style: "dark",
                links: [
                    {
                        title: "Documentation Pages",
                        items: [
                            {
                                label: "Quickstart",
                                to: "docs/getting-started/intro"
                            },
                            {
                                label: "Documentation",
                                to: "docs/intro"
                            }
                        ]
                    },
                    {
                        title: "More",
                        items: [
                            {
                                label: "Blog",
                                to: "/blog"
                            },
                            {
                                label: "GitHub",
                                href:
                                    "https://github.com/" +
                                    "shrimpster00/sparkdown"
                            }
                        ]
                    }
                ],
                copyright:
                    "Copyright &copy; 2021 Cayden Lund. \
                    Site built with Docusaurus."
            },
            prism: {
                theme: lightCodeTheme,
                darkTheme: darkCodeTheme,
                additionalLanguages: ["latex"]
            }
        })
};

module.exports = config;
