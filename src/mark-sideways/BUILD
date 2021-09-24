cc_library(
    name = "mark-sideways-helpers",
    srcs = ["mark-sideways-helpers.cc"],
    hdrs = ["mark-sideways-helpers.h"],
    deps = [ "//lib/parser" ]
)

cc_binary(
    name = "mark-sideways",
    srcs = ["mark-sideways.cc"],
    deps = [ ":mark-sideways-helpers" ]
)