cc_library(
    name = "enumerate",
    srcs = ["enumerate.cpp"],
    hdrs = ["enumerate.hpp"],
    visibility = ["//lexer:__subpackages__"],
    deps = [
        "//lexer/lexers/abstract-lexer",
        "//state",
    ],
)

cc_test(
    name = "enumerate.test",
    size = "small",
    srcs = ["enumerate.test.cpp"],
    deps = [
        ":enumerate",
        "//state",
        "@googletest//:gtest_main",
    ],
)
