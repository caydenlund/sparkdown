cc_library(
    name = "sparkdown.lib",
    srcs = ["sparkdown.cpp"],
    hdrs = ["sparkdown.hpp"],
    visibility = ["//visibility:public"],
    deps = [],
)

cc_binary(
    name = "sparkdown",
    srcs = ["executable.cpp"],
    deps = [
        ":sparkdown.lib",
        "@cpp_utilities//:argh",
    ],
)
