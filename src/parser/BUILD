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
    name = "parser.arrow.test",
    size = "small",
    srcs = ["tests/arrow.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.enumerate.test",
    size = "small",
    srcs = ["tests/enumerate.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.header.test",
    size = "small",
    srcs = ["tests/header.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.itemize.test",
    size = "small",
    srcs = ["tests/itemize.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)
