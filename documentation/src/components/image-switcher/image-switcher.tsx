// src/image-switcher/image-switcher.tsx
// v. 1.0.0
//
// Author: Cayden Lund
//   Date: 10/21/2021
//
// This file is part of Sparkdown, a new markup/markdown language
// for quickly writing and formatting notes.
//
// This file contains the ImageSwitcher component, which is used to
// switch between two images based on the current theme.
//
// Copyright (C) 2021 Cayden Lund <https://github.com/shrimpster00>
// License: MIT <https://opensource.org/licenses/MIT>

import * as React from "react";
import useThemeContext from "@theme/hooks/useThemeContext";

const ImageSwitcher = ({lightImage, darkImage}: any) => {
    const {isDarkTheme} = useThemeContext();

    return (
        <img src={isDarkTheme ? darkImage.default : lightImage.default} alt=""/>
    )
}

export default ImageSwitcher;
