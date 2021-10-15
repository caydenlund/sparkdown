cc_library(
    name = "itemize",
    srcs = ["itemize.cpp"],
    hdrs = ["itemize.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "itemize.test",
    size = "small",
    srcs = ["itemize.test.cpp"],
    deps = [
        ":itemize",
        "//state",
        "@googletest//:gtest_main",
    ],
)
