cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    deps = [
        ":state",
        "//lexer"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "state",
    srcs = ["state.cpp"],
    hdrs = ["state.hpp"],
    visibility = [
        "//parser:__subpackages__",
        "//lexer:__subpackages__"
    ]
)
