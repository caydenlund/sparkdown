cc_library(
    name = "token",
    srcs = ["token.cpp"],
    hdrs = ["token.hpp"],
    deps = ["//state"],
    visibility = ["//lexer:__subpackages__"]
)

cc_test(
    name = "token.test",
    size = "small",
    srcs = ["token.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//state",
        ":token"
    ]
)
