cc_library(
    name = "verbatim",
    srcs = ["verbatim.cpp"],
    hdrs = ["verbatim.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "verbatim.test",
    size = "small",
    srcs = ["verbatim.test.cpp"],
    deps = [
        ":verbatim",
        "//state",
        "@googletest//:gtest_main",
    ],
)
