cc_binary(
    name = "rocksdb_demo",
    srcs = ["src/rocksdb_main.cpp"],
    deps = [
        "//external:rocksdb",
    ],
)

cc_binary(
    name = "counter_server",
    srcs = ["src/example/counter/server.cpp"],
    copts = [
        "-DGFLAGS_NS=google",
    ],
    includes = [
        "src/example/counter",
    ],
    deps = [
        ":counter_cc_proto",
        "//external:braft",
        "//external:rocksdb",
    ],
)

cc_binary(
    name = "counter_client",
    srcs = ["src/example/counter/client.cpp"],
    copts = [
        "-DGFLAGS_NS=google",
    ],
    includes = [
        "src/example/counter",
    ],
    deps = [
        ":counter_cc_proto",
        "//external:braft",
    ],
)

proto_library(
    name = "counter_proto",
    srcs = [
        "src/example/counter/counter.proto",
    ],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "counter_cc_proto",
    deps = [
        ":counter_proto",
    ],
    visibility = ["//visibility:public"],
)
