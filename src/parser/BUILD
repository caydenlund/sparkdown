cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    visibility = ["//visibility:public"],
    deps = [
        "//lexer",
        "//state",
    ],
)

cc_test(
    name = "parser.test",
    size = "small",
    srcs = ["parser.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)
