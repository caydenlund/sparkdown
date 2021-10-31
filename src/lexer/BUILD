cc_library(
    name = "lexer",
    srcs = ["lexer.cpp"],
    hdrs = ["lexer.hpp"],
    visibility = ["//parser:__subpackages__"],
    deps = [
        "//token",
    ],
)

cc_test(
    name = "lexer.test",
    size = "small",
    srcs = ["lexer.test.cpp"],
    deps = [
        ":lexer",
        "@googletest//:gtest_main",
    ],
)
