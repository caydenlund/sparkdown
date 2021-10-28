cc_library(
    name = "verb-block",
    srcs = ["verb-block.cpp"],
    hdrs = ["verb-block.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "verb-block.test",
    size = "small",
    srcs = ["verb-block.test.cpp"],
    deps = [
        ":verb-block",
        "//state",
        "@googletest//:gtest_main",
    ],
)
