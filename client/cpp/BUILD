cc_library(
    name = "assfire_router_cc_client",
    srcs = [
        "assfire/router/client/CompletableRouteMatrix.cpp",
        "assfire/router/client/CompletableRouteMatrix.hpp",
        "assfire/router/client/RouterClient.cpp",
    ],
    hdrs = ["assfire/router/client/RouterClient.hpp", "assfire/router/client/RouterClientSettings.hpp"],
    copts = ["/std:c++20"],
    include_prefix = "assfire/router/client",
    strip_include_prefix = "assfire/router/client",
    deps = [
        "//api/cpp:assfire_router_cc_api",
        "//api/cpp:assfire_router_cc_proto_serialization",
        "//api/proto:assfire_router_cc_grpc",
        "//engine/cpp:assfire_router_cc_matrix",
    ],
)
