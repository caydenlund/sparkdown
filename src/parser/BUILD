cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    deps = [
        ":state",
        "//parser/lexers:itemize"
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "state",
    srcs = ["state.cpp"],
    hdrs = ["state.hpp"],
    visibility = ["//parser:__subpackages__"]
)

cc_library(
    name = "lexer",
    srcs = ["lexer.cpp"],
    hdrs = ["lexer.hpp"],
    deps = [":state"],
    visibility = ["//parser:__subpackages__"]
)
