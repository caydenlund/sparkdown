cc_library(
    name = "arrow",
    srcs = ["arrow.cpp"],
    hdrs = ["arrow.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "arrow.test",
    size = "small",
    srcs = ["arrow.test.cpp"],
    deps = [
        ":arrow",
        "//state",
        "@googletest//:gtest_main",
    ],
)
