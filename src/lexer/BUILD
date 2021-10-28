cc_library(
    name = "lexer",
    srcs = ["lexer.cpp"],
    hdrs = ["lexer.hpp"],
    visibility = ["//parser:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//lexer/lexers/arrow",
        "//lexer/lexers/bold",
        "//lexer/lexers/enumerate",
        "//lexer/lexers/header",
        "//lexer/lexers/italic",
        "//lexer/lexers/itemize",
        "//lexer/lexers/section",
        "//lexer/lexers/text",
        "//lexer/lexers/verbatim",
    ],
)

cc_test(
    name = "lexer.test",
    size = "small",
    srcs = ["lexer.test.cpp"],
    deps = [
        ":lexer",
        "//state",
        "@googletest//:gtest_main",
    ],
)
