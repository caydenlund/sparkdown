cc_library(
    name = "mark-sideways.lib",
    srcs = ["mark-sideways.cpp"],
    hdrs = ["mark-sideways.hpp"],
    visibility = ["//visibility:public"],
    deps = ["//parser"],
)

cc_binary(
    name = "mark-sideways",
    srcs = ["executable.cpp"],
    deps = [":mark-sideways.lib"],
)
