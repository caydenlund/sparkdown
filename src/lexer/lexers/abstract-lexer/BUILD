cc_library(
    name = "abstract-lexer",
    srcs = ["abstract-lexer.cpp"],
    hdrs = ["abstract-lexer.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/token",
        "//state",
    ],
)

cc_test(
    name = "abstract-lexer.test",
    size = "small",
    srcs = ["abstract-lexer.test.cpp"],
    deps = [
        ":abstract-lexer",
        "//state",
        "@googletest//:gtest_main",
    ],
)
