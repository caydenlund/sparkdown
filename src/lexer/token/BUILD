cc_library(
    name = "token",
    srcs = ["token.cpp"],
    hdrs = ["token.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = ["//state"],
)

cc_test(
    name = "token.test",
    size = "small",
    srcs = ["token.test.cpp"],
    deps = [
        ":token",
        "//state",
        "@googletest//:gtest_main",
    ],
)
