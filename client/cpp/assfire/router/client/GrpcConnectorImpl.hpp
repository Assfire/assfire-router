#pragma once

#include "assfire/api/v1/router/router.grpc.pb.h"
#include "GrpcConnector.hpp"
#include "RouterConnectionSettings.hpp"
#include <memory>

namespace assfire::router
{
    class GrpcConnectorImpl : public GrpcConnector
    {
    public:
        GrpcConnectorImpl(const RouterConnectionSettings &settings);

        virtual RouterServiceStub &get_router_stub() override;
        virtual ConfigurationServiceStub &get_configuration_stub() override;

    private:
        std::shared_ptr<::grpc::Channel> channel;
        std::unique_ptr<RouterServiceStub> router_stub;
        std::unique_ptr<ConfigurationServiceStub> configuration_stub;
    };
}