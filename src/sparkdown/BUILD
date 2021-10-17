cc_library(
    name = "sparkdown.lib",
    srcs = ["sparkdown.cpp"],
    hdrs = ["sparkdown.hpp"],
    visibility = ["//visibility:public"],
    deps = ["//parser"],
)

cc_binary(
    name = "sparkdown",
    srcs = ["executable.cpp"],
    deps = [":sparkdown.lib"],
)
