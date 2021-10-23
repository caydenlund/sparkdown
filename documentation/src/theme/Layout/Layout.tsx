// src/theme/Layout/Layout.tsx
// v. 0.1.0
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of Sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a wrapper around the original Docusaurus Layout
// component. This wrapper is used to add some additional <meta> tags
// to the <head> of the page.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// npm imports.
import * as React from "react";
import Head from "@docusaurus/Head";
import OriginalLayout from "@theme-original/Layout";

// The Layout component.
//   <Layout title="Sparkdown" description="A new markup/markdown language
//                               for quickly writing and formatting notes.">
//       ...
//       <main>
//           ...
//       </main>
//   </Layout>
//
// * string props.title (optional)       - The title of the page.
// * string props.description (optional) - The description of the page.
//                                         This description is not reflected as
//                                         page content, but is used for
//                                         SEO purposes.
const Layout = (props: any) => {
    return (
        <>
            <Head>
                {/* Metadata regarding the favicon. */}
                <link
                    rel="apple-touch-icon"
                    sizes="180x180"
                    href="/img/favicon/apple-touch-icon.png"
                />
                <link
                    rel="icon"
                    type="image/png"
                    sizes="32x32"
                    href="/img/favicon/favicon-32x32.png"
                />
                <link
                    rel="icon"
                    type="image/png"
                    sizes="16x16"
                    href="/img/favicon/favicon-16x16.png"
                />
                <link
                    rel="mask-icon"
                    href="/img/favicon/safari-pinned-tab.svg"
                    color="#c0392b"
                />
                <link rel="shortcut icon" href="/img/favicon/favicon.ico" />
                <meta name="msapplication-TileColor" content="#da532c" />
            </Head>

            {/* And here we use the original Docusaurus Layout component. */}
            <OriginalLayout {...props} />
        </>
    );
};

export default Layout;
