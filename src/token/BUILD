cc_library(
    name = "token",
    srcs = ["token.cpp"],
    hdrs = ["token.hpp"],
    visibility = [
        "//lexer:__subpackages__",
        "//parser:__subpackages__",
    ],
)

cc_test(
    name = "token.tests",
    size = "small",
    srcs = ["token.tests.cpp"],
    deps = [
        ":token",
        "@googletest//:gtest_main",
    ],
)
