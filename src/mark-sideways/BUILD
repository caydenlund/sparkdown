cc_library(
    name = "mark-sideways.lib",
    srcs = ["mark-sideways.cc"],
    hdrs = ["mark-sideways.h"],
    deps = [ "//parser" ],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "mark-sideways",
    srcs = ["executable.cc"],
    deps = [ ":mark-sideways.lib" ]
)