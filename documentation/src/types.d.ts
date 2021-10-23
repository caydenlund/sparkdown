// src/types.d.ts
// v. 1.0.0
//
// Author: Cayden Lund
//   Date: 10/17/2021
//
// This file is part of Sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains a couple of type definitions for the
// TypeScript compiler.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

/// <reference types="@docusaurus/module-type-aliases" />
/// <reference types="@docusaurus/theme-classic" />

declare module "*.png" {
    const value: any;
    export = value;
}
