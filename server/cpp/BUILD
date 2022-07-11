cc_library(
    name = "assfire_router_cc_service_impl",
    srcs = ["RouterServiceImpl.cpp"],
    hdrs = ["RouterServiceImpl.hpp"],
    copts = ["/std:c++20"],
    deps = [
        "//api/proto:assfire_router_cc_grpc",
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
    copts = ["/std:c++20"],
    deps = [":assfire_router_cc_service_impl"],
)
