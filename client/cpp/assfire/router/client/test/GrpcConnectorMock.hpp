#pragma once

#include "assfire/api/v1/router/router.grpc.pb.h"
#include "assfire/router/client/GrpcConnector.hpp"
#include <memory>

namespace assfire::router
{
    class GrpcConnectorMock : public GrpcConnector
    {
    public:
        GrpcConnectorMock(RouterServiceStub &router_stub, ConfigurationServiceStub &configuration_stub) : router_stub(router_stub),
                                                                                                          configuration_stub(configuration_stub)
        {
        }

        virtual RouterServiceStub &get_router_stub() override
        {
            return router_stub;
        }

        virtual ConfigurationServiceStub &get_configuration_stub() override
        {
            return configuration_stub;
        }

    private:
        RouterServiceStub &router_stub;
        ConfigurationServiceStub &configuration_stub;
    };
}