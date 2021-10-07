cc_library(
    name = "itemize",
    srcs = ["itemize.cpp"],
    hdrs = ["itemize.hpp"],
    deps = [
        "//parser:state",
        "//lexer/lexers/abstractLexer"
    ],
    visibility = ["//lexer:__subpackages__"]
)

cc_test(
    name = "itemize.test",
    size = "small",
    srcs = ["itemize.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//parser:state",
        ":itemize"
    ]
)
