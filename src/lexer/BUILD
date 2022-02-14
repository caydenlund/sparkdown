cc_library(
    name = "lexer",
    srcs = ["lexer.cpp"],
    hdrs = ["lexer.hpp"],
    visibility = ["//parser:__subpackages__"],
    deps = [
        "//token",
    ],
)

cc_test(
    name = "lexer.tests",
    size = "small",
    srcs = ["lexer.tests.cpp"],
    deps = [
        ":lexer",
        "@googletest//:gtest_main",
    ],
)
