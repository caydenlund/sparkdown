cc_library(
    name = "lexer",
    srcs = ["lexer.cpp"],
    hdrs = ["lexer.hpp"],
    visibility = ["//parser:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//lexer/lexers/enumerate",
        "//lexer/lexers/header",
        "//lexer/lexers/itemize",
        "//lexer/lexers/section",
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
