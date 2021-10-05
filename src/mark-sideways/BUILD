cc_library(
    name = "mark-sideways.lib",
    srcs = ["mark-sideways.cpp"],
    hdrs = ["mark-sideways.hpp"],
    deps = [ "//parser" ],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "mark-sideways",
    srcs = ["executable.cpp"],
    deps = [ ":mark-sideways.lib" ]
)
