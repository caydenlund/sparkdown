cc_library(
    name = "section",
    srcs = ["section.cpp"],
    hdrs = ["section.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "section.test",
    size = "small",
    srcs = ["section.test.cpp"],
    deps = [
        ":section",
        "//state",
        "@googletest//:gtest_main",
    ],
)
