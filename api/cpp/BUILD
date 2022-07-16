cc_library(
    name = "assfire_router_cc_api",
    srcs = [
        "assfire/router/api/Api.cpp",
    ],
    hdrs = [
        "assfire/router/api/GeoPoint.hpp",
        "assfire/router/api/Route.hpp",
        "assfire/router/api/RouteInfo.hpp",
        "assfire/router/api/RouteMatrix.hpp",
        "assfire/router/api/RoutesProvider.hpp",
        "assfire/router/api/RoutingStrategyId.hpp",
        "assfire/router/api/TransportProfileId.hpp",
    ],
    include_prefix = "assfire/router/api",
    strip_include_prefix = "assfire/router/api",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "assfire_router_cc_proto_serialization",
    hdrs = ["assfire/router/api/proto/ProtoSerialization.hpp"],
    include_prefix = "assfire/router/api/proto",
    strip_include_prefix = "assfire/router/api/proto",
    visibility = ["//visibility:public"],
    deps = [":assfire_router_cc_api", "//api/proto:assfire_router_cc_proto"]
)
