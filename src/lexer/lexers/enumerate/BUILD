cc_library(
    name = "enumerate",
    srcs = ["enumerate.cpp"],
    hdrs = ["enumerate.hpp"],
    deps = [
        "//state",
        "//lexer/lexers/abstract-lexer"
    ],
    visibility = ["//lexer:__subpackages__"]
)

cc_test(
    name = "enumerate.test",
    size = "small",
    srcs = ["enumerate.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        "//state",
        ":enumerate"
    ]
)
