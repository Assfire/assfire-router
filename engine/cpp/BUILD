cc_library(
    name = "assfire_router_cc_engine_common",
    srcs = [
        "assfire/router/engine/common/EngineCommon.cpp",
    ],
    hdrs = [
        "assfire/router/engine/common/RoutingStrategy.hpp",
        "assfire/router/engine/common/TransportProfile.hpp",
    ],
    deps = [
        "//api/cpp:assfire_router_cc_api",
    ],
    strip_include_prefix = "assfire/router/engine/common/",
    include_prefix = "assfire/router/engine/common/",
    copts = ["/std:c++20"],
)

cc_library(
    name = "assfire_router_cc_matrix",
    srcs = ["assfire/router/engine/matrix/ImmutableRouteMatrix.cpp"],
    hdrs = ["assfire/router/engine/matrix/ImmutableRouteMatrix.hpp"],
    deps = [
        "//api/cpp:assfire_router_cc_api",
        ":assfire_router_cc_engine_common",
    ],
    strip_include_prefix = "assfire/router/engine/matrix/",
    include_prefix = "assfire/router/engine/matrix/",
    visibility = ["//visibility:public"],
    copts = ["/std:c++20"]
)

cc_library(
    name = "assfire_router_cc_engine",
    srcs = [
        "assfire/router/engine/RouterEngine.cpp",
        "assfire/router/engine/algorithms/BasicRoutingStrategy.cpp",
        "assfire/router/engine/algorithms/CrowflightRoutingStrategy.cpp",
        "assfire/router/engine/algorithms/InfinityRoutingStrategy.cpp",
        "assfire/router/engine/algorithms/CrowflightCalculator.hpp",
    ],
    hdrs = [
        "assfire/router/engine/RouterEngine.hpp",
        "assfire/router/engine/RoutingStrategyProvider.hpp",
        "assfire/router/engine/TransportProfileProvider.hpp",
        "assfire/router/engine/algorithms/BasicRoutingStrategy.hpp",
        "assfire/router/engine/algorithms/CrowflightRoutingStrategy.hpp",
        "assfire/router/engine/algorithms/InfinityRoutingStrategy.hpp",
    ],
    deps = [
        ":assfire_router_cc_engine_common",
        ":assfire_router_cc_matrix",
        "//api/cpp:assfire_router_cc_api",
    ],
    visibility = ["//visibility:public"],
    copts = ["/std:c++20"]
)
