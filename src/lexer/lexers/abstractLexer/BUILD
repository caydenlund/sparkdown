cc_library(
    name = "abstractLexer",
    srcs = ["abstractLexer.cpp"],
    hdrs = ["abstractLexer.hpp"],
    deps = ["//parser:state"],
    visibility = ["//lexer:__subpackages__"]
)

cc_test(
    name = "abstractLexer.test",
    size = "small",
    srcs = ["abstractLexer.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//parser:state",
        ":abstractLexer"
    ]
)
