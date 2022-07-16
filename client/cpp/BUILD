cc_library(
    name = "assfire_router_cc_client",
    srcs = [
        "assfire/router/client/CompletableRouteMatrix.cpp",
        "assfire/router/client/CompletableRouteMatrix.hpp",
        "assfire/router/client/GrpcConnectorImpl.cpp",
        "assfire/router/client/RouterClient.cpp",
    ],
    hdrs = [
        "assfire/router/client/GrpcConnector.hpp",
        "assfire/router/client/GrpcConnectorImpl.hpp",
        "assfire/router/client/RouterClient.hpp",
        "assfire/router/client/RouterConnectionSettings.hpp",
    ],
    include_prefix = "assfire/router/client",
    strip_include_prefix = "assfire/router/client",
    deps = [
        "//api/cpp:assfire_router_cc_api",
        "//api/cpp:assfire_router_cc_proto_serialization",
        "//api/proto:assfire_router_cc_grpc",
        "//engine/cpp:assfire_router_cc_matrix",
    ],
)

cc_test(
    name = "assfire_router_cc_client_test",
    srcs = [
        "assfire/router/client/test/GrpcConnectorMock.hpp",
        "assfire/router/client/test/ProtoMatchers.hpp",
        "assfire/router/client/test/RouterClient_Test.cpp",
    ],

    deps = [
        ":assfire_router_cc_client",
        "@com_google_googletest//:gtest_main"
    ],
)
