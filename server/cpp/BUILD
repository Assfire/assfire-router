load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")

cc_library(
    name = "assfire_router_cc_service_impl",
    srcs = [
        "ConfigurationServiceImpl.cpp",
        "RouterServiceImpl.cpp",
    ],
    hdrs = [
        "ConfigurationServiceImpl.hpp",
        "RouterServiceImpl.hpp",
    ],
    deps = [
        "//api/proto:assfire_router_cc_grpc",
        "//api/cpp:assfire_router_cc_proto_serialization",
        "//engine/cpp:assfire_router_cc_engine",
    ],
)

cc_binary(
    name = "assfire_router_cc_server",
    srcs = [
        "ArgsSettingsLoader.hpp",
        "PropsSettingsLoader.hpp",
        "Settings.hpp",
        "SettingsLoader.hpp",
        "main.cpp",
    ],
    deps = [":assfire_router_cc_service_impl"],
)

cc_image(
    name = "assfire_router_cc_image",
    binary = ":assfire_router_cc_server",
)