cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    visibility = ["//sparkdown:__subpackages__"],
    deps = [
        "//lexer",
        "//token",
    ],
)

cc_test(
    name = "parser.header.test",
    size = "small",
    srcs = ["parser.header.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)
