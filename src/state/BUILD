cc_library(
    name = "state",
    srcs = ["state.cpp"],
    hdrs = ["state.hpp"],
    visibility = [
        "//parser:__subpackages__",
        "//lexer:__subpackages__"
    ]
)

cc_test(
    name = "state.test",
    size = "small",
    srcs = ["state.test.cpp"],
    deps = [
        "@googletest//:gtest_main",
        ":state"
    ]
)
