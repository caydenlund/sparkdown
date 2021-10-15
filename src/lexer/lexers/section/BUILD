cc_library(
    name = "section",
    srcs = ["section.cpp"],
    hdrs = ["section.hpp"],
    deps = [
        "//state",
        "//lexer/lexers/abstract-lexer"
    ],
    visibility = ["//lexer:__subpackages__"]
)

cc_test(
    name = "section.test",
    size = "small",
    srcs = ["section.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//state",
        ":section"
    ]
)

