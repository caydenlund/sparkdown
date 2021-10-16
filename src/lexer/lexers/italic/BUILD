cc_library(
    name = "italic",
    srcs = ["italic.cpp"],
    hdrs = ["italic.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "italic.test",
    size = "small",
    srcs = ["italic.test.cpp"],
    deps = [
        ":italic",
        "//state",
        "@googletest//:gtest_main",
    ],
)
