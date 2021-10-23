// src/pages/index.tsx
// v. 1.0.0
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of Sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the index page.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

// npm imports.
import * as React from "react";
import clsx from "clsx";
import Layout from "@theme/Layout";
import Link from "@docusaurus/Link";

// Local imports.
import styles from "./index.module.css";

// Represents a single button in the hero banner.
//   <HeroBannerButton to="/docs/getting-started" text="Get Started" />
//
// * string to   - The URL to link to.
// * string text - The text to display on the button.
const HeroBannerButton = ({to, text}: {to: string; text: string}) => (
    <div className="col col--4">
        <Link
            className={clsx(
                "button",
                "button--secondary button--lg",
                styles.button
            )}
            to={to}
        >
            {text}
        </Link>
    </div>
);

// Represents the hero banner.
//   <HeroBanner />
const HeroBanner = () => (
    <header className={clsx("hero hero--primary", styles.heroBanner)}>
        <div className="container">
            <h1 className="hero__title">Sparkdown</h1>
            <p className="hero__subtitle">
                A new markup/markdown language for quickly taking notes.
            </p>
            <div className={clsx("row", styles.buttons)}>
                <HeroBannerButton
                    to="/docs/getting-started/intro"
                    text="Get Started"
                />
                <HeroBannerButton to="/docs/intro" text="Read the Docs" />
            </div>
        </div>
    </header>
);

// Represents a single feature in the features section.
//   <Feature SVG={require("/img/lightning_bolt.svg")} title="Lightning-quick"
//            description="Enjoy the performance benefits of plain old C++." />
//
// * React.ComponentType SVG - The SVG to display.
// * string title            - The title of the feature.
// * string description      - The description of the feature.
const Feature = ({
    SVG,
    title,
    description
}: {
    SVG: React.ComponentType<any>;
    title: string;
    description: string;
}) => (
    <div className="col col--4">
        <div className="text--center">
            <SVG className={styles.featureSVG} alt={title} />
        </div>
        <div className="text--center padding-horiz--md">
            <h3>{title}</h3>
            <p>{description}</p>
        </div>
    </div>
);

// Represents the features section.
//   <Features />
const Features = () => (
    <div className={clsx("row", styles.features)}>
        {/* Feature 1: Lightning-quick. */}
        <Feature
            SVG={require("/img/lightning_bolt.svg").default}
            title="Lightning-quick"
            description="Enjoy the performance benefits of plain old C++."
        />
        {/* Feature 2: Familiar. */}
        <Feature
            SVG={require("/img/computer_heart.svg").default}
            title="Familiar"
            description="Use markdown syntax and LaTeX syntax simultaneously."
        />
        {/* Feature 3: Powerful. */}
        <Feature
            SVG={require("/img/engine.svg").default}
            title="Powerful"
            description="Uses LaTeX under the hood to render notes to PDF."
        />
    </div>
);

const Home = () => (
    <Layout>
        <HeroBanner />

        <main>
            <Features />
        </main>
    </Layout>
);

export default Home;
