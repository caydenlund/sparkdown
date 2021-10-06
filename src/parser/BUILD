cc_library(
    name = "parser",
    srcs = ["parser.cpp"],
    hdrs = ["parser.hpp"],
    deps = [":state"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "state",
    srcs = ["state.cpp"],
    hdrs = ["state.hpp"],
    visibility = ["//parser:__subpackages__"]
)
