cc_library(
    name = "header",
    srcs = ["header.cpp"],
    hdrs = ["header.hpp"],
    deps = [
        "//state",
        "//lexer/lexers/abstract-lexer"
    ],
    visibility = ["//lexer:__subpackages__"]
)

cc_test(
    name = "header.test",
    size = "small",
    srcs = ["header.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//state",
        ":header"
    ]
)
