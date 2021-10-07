cc_library(
    name = "lexer",
    srcs = ["lexer.cpp"],
    hdrs = ["lexer.hpp"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//lexer/lexers/enumerate",
        "//lexer/lexers/itemize"
    ],
    visibility = ["//parser:__subpackages__"]
)

cc_test(
    name = "lexer.test",
    size = "small",
    srcs = ["lexer.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//parser:state",
        ":lexer"
    ]
)
