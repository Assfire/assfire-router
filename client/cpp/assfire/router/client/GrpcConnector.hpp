#pragma once

#include "assfire/api/v1/router/router.grpc.pb.h"

namespace assfire::router
{
    class GrpcConnector
    {
    public:
        using RouterServiceStub = assfire::api::v1::router::RouterService::StubInterface;
        using ConfigurationServiceStub = assfire::api::v1::router::ConfigurationService::StubInterface;

        virtual ~GrpcConnector() = default;

        virtual RouterServiceStub &get_router_stub() = 0;
        virtual ConfigurationServiceStub &get_configuration_stub() = 0;
    };
}