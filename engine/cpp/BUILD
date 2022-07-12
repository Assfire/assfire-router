cc_library(
    name = "assfire_router_cc_engine_common",
    srcs = [
        "assfire/router/engine/common/EngineCommon.cpp",
    ],
    hdrs = [
        "assfire/router/engine/common/RoutingStrategy.hpp",
        "assfire/router/engine/common/TransportProfile.hpp",
    ],
    copts = ["/std:c++20"],
    include_prefix = "assfire/router/engine/common/",
    strip_include_prefix = "assfire/router/engine/common/",
    deps = [
        "//api/cpp:assfire_router_cc_api",
    ],
)

cc_library(
    name = "assfire_router_cc_matrix",
    srcs = ["assfire/router/engine/matrix/ImmutableRouteMatrix.cpp"],
    hdrs = ["assfire/router/engine/matrix/ImmutableRouteMatrix.hpp"],
    copts = ["/std:c++20"],
    include_prefix = "assfire/router/engine/matrix/",
    strip_include_prefix = "assfire/router/engine/matrix/",
    visibility = ["//visibility:public"],
    deps = [
        ":assfire_router_cc_engine_common",
        "//api/cpp:assfire_router_cc_api",
    ],
)

cc_library(
    name = "assfire_router_cc_engine",
    srcs = [
        "assfire/router/engine/BasicRoutingStrategyProvider.cpp",
        "assfire/router/engine/BasicTransportProfileProvider.cpp",
        "assfire/router/engine/RouterEngine.cpp",
        "assfire/router/engine/algorithms/BasicRoutingStrategy.cpp",
        "assfire/router/engine/algorithms/CrowflightCalculator.hpp",
        "assfire/router/engine/algorithms/CrowflightRoutingStrategy.cpp",
        "assfire/router/engine/algorithms/InfinityRoutingStrategy.cpp",
    ],
    hdrs = [
        "assfire/router/engine/BasicRoutingStrategyProvider.hpp",
        "assfire/router/engine/BasicTransportProfileProvider.hpp",
        "assfire/router/engine/RouterEngine.hpp",
        "assfire/router/engine/RoutingStrategyProvider.hpp",
        "assfire/router/engine/TransportProfileProvider.hpp",
        "assfire/router/engine/algorithms/BasicRoutingStrategy.hpp",
        "assfire/router/engine/algorithms/CrowflightRoutingStrategy.hpp",
        "assfire/router/engine/algorithms/InfinityRoutingStrategy.hpp",
    ],
    copts = ["/std:c++20"],
    include_prefix = "assfire/router/engine/",
    strip_include_prefix = "assfire/router/engine/",
    visibility = ["//visibility:public"],
    deps = [
        ":assfire_router_cc_engine_common",
        ":assfire_router_cc_matrix",
        "//api/cpp:assfire_router_cc_api",
    ],
)
