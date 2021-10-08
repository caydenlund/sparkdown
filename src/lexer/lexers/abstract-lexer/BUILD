cc_library(
    name = "abstract-lexer",
    srcs = ["abstract-lexer.cpp"],
    hdrs = ["abstract-lexer.hpp"],
    deps = [
        "//state",
        "//lexer/token",
    ],
    visibility = ["//lexer:__subpackages__"]
)

cc_test(
    name = "abstract-lexer.test",
    size = "small",
    srcs = ["abstract-lexer.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//state",
        ":abstract-lexer"
    ]
)
