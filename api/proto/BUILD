load("@rules_proto_grpc//go:defs.bzl", "go_grpc_library", "go_proto_library")
load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library", "cpp_proto_library")

proto_library(
    name = "assfire_router_concepts_proto",
    srcs = ["assfire/api/v1/router/concepts.proto"],
    import_prefix = "assfire/api/v1/router/",
    strip_import_prefix = "assfire/api/v1/router/",
    visibility = ["//visibility:public"],
    deps = ["@assfire_common_concepts//api/proto:assfire_concepts_proto"],
)

proto_library(
    name = "assfire_router_grpc_proto",
    srcs = ["assfire/api/v1/router/grpc.proto"],
    deps = [":assfire_router_concepts_proto"],
    import_prefix = "assfire/api/v1/router/",
    strip_import_prefix = "assfire/api/v1/router/",
    visibility = ["//visibility:public"],
)

cpp_proto_library(
    name = "assfire_router_concepts_cc_proto",
    protos = [
        ":assfire_router_concepts_proto",
        "@assfire_common_concepts//api/proto:assfire_concepts_proto",
    ],
    visibility = ["//visibility:public"],
)

cpp_grpc_library(
    name = "assfire_router_cc_grpc",
    protos = [
        ":assfire_router_concepts_proto",
        ":assfire_router_grpc_proto",
    ],
    visibility = ["//visibility:public"],
    deps = ["assfire_router_concepts_cc_proto"],
)
