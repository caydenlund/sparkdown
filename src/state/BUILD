cc_library(
    name = "state",
    srcs = ["state.cpp"],
    hdrs = ["state.hpp"],
    visibility = [
        "//lexer:__subpackages__",
        "//parser:__subpackages__",
    ],
)

cc_test(
    name = "state.test",
    size = "small",
    srcs = ["state.test.cpp"],
    deps = [
        ":state",
        "@googletest//:gtest_main",
    ],
)
