cc_library(
    name = "token",
    srcs = ["token.cpp"],
    hdrs = ["token.hpp"],
    visibility = ["//lexer:__subpackages__"],
)

cc_test(
    name = "token.test",
    size = "small",
    srcs = ["token.test.cpp"],
    deps = [
        ":token",
        "@googletest//:gtest_main",
    ],
)
