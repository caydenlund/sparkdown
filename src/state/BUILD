cc_library(
    name = "state",
    srcs = ["state.cpp"],
    hdrs = ["state.hpp"],
    visibility = [
        "//parser:__subpackages__",
    ],
)

cc_test(
    name = "state.tests",
    size = "small",
    srcs = ["state.tests.cpp"],
    deps = [
        ":state",
        "@googletest//:gtest_main",
    ],
)
