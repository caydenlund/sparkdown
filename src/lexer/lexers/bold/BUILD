cc_library(
    name = "bold",
    srcs = ["bold.cpp"],
    hdrs = ["bold.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "bold.test",
    size = "small",
    srcs = ["bold.test.cpp"],
    deps = [
        ":bold",
        "//state",
        "@googletest//:gtest_main",
    ],
)
