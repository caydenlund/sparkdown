cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    deps = [
        "//state",
        "//lexer"
    ],
    visibility = ["//visibility:public"]
)

cc_test(
    name = "parser.test",
    size = "small",
    srcs = ["parser.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        ":parser"
    ]
)
