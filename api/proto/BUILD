load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library", "cpp_proto_library")

proto_library(
    name = "assfire_router_proto",
    srcs = ["assfire/api/v1/router/router.proto"],
    import_prefix = "assfire/api/v1/router/",
    strip_import_prefix = "assfire/api/v1/router/",
    visibility = ["//visibility:public"]
)

cpp_proto_library(
    name = "assfire_router_cc_proto",
    protos = [
        ":assfire_router_proto"
    ],
    visibility = ["//visibility:public"],
)

cpp_grpc_library(
    name = "assfire_router_cc_grpc",
    protos = [
        ":assfire_router_proto",
    ],
    visibility = ["//visibility:public"],
    deps = [":assfire_router_cc_proto"],
)
