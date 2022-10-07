cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    visibility = [
        "//parser:__subpackages__",
        "//sparkdown:__subpackages__",
    ],
    deps = [
        "//lexer",
        "//parser/patterns:pattern",
        "//state",
        "//token",
    ],
)

cc_test(
    name = "parser.tests",
    size = "small",
    srcs = ["parser.tests.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)
