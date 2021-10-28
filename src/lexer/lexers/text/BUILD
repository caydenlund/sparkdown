cc_library(
    name = "text",
    srcs = ["text.cpp"],
    hdrs = ["text.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "text.test",
    size = "small",
    srcs = ["text.test.cpp"],
    deps = [
        ":text",
        "//state",
        "@googletest//:gtest_main",
    ],
)
