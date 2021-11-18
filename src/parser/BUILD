cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    visibility = ["//sparkdown:__subpackages__"],
    deps = [
        "//lexer",
        "//token",
    ],
)

cc_test(
    name = "parser.arrow.test",
    size = "small",
    srcs = ["tests/arrow.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.enumerate.test",
    size = "small",
    srcs = ["tests/enumerate.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.footer.test",
    size = "small",
    srcs = ["tests/footer.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.header.test",
    size = "small",
    srcs = ["tests/header.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.headline.test",
    size = "small",
    srcs = ["tests/headline.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.itemize.test",
    size = "small",
    srcs = ["tests/itemize.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.math.block.test",
    size = "small",
    srcs = ["tests/math.block.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.math.inline.test",
    size = "small",
    srcs = ["tests/math.inline.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.verb.block.test",
    size = "small",
    srcs = ["tests/verb.block.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "parser.verb.inline.test",
    size = "small",
    srcs = ["tests/verb.inline.test.cpp"],
    deps = [
        ":parser",
        "@googletest//:gtest_main",
    ],
)
