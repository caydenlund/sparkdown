cc_library(
    name = "header",
    srcs = ["header.cpp"],
    hdrs = ["header.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "header.test",
    size = "small",
    srcs = ["header.test.cpp"],
    deps = [
        ":header",
        "//state",
        "@googletest//:gtest_main",
    ],
)
