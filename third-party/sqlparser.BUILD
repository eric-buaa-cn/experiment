package(default_visibility = ["//visibility:public"])

cc_library(
    name = "sqlparser",
    srcs = glob([
        "src/*.cpp",
        "src/sql/*.cpp",
        "src/parser/*.cpp",
        "src/util/*.cpp",
        "src/*.h",
        "src/sql/*.h",
        "src/parser/*.h",
        "src/util/*.h",
    ]),
    hdrs = glob([
        "src/*.h",
        "src/sql/*.h",
        "src/parser/*.h",
        "src/util/*.h",
    ]),
    strip_include_prefix = "src",
    include_prefix = "sqlparser",
)
