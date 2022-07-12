#pragma once

#include <memory>
#include "assfire/api/v1/router/router.grpc.pb.h"
#include "assfire/router/engine/RoutingStrategyProvider.hpp"
#include "assfire/router/engine/TransportProfileProvider.hpp"

namespace assfire::router
{
    class ConfigurationServiceImpl : public assfire::api::v1::router::ConfigurationService::Service
    {
    public:
        ConfigurationServiceImpl(std::shared_ptr<RoutingStrategyProvider> routing_strategies_provider,
                                 std::shared_ptr<TransportProfileProvider> transport_profiles_provider);

        virtual ::grpc::Status GetAvailableStrategies(::grpc::ServerContext *context,
                                                      const ::assfire::api::v1::router::GetAvailableStrategiesRequest *request,
                                                      ::assfire::api::v1::router::GetAvailableStrategiesResponse *response) override;
        virtual ::grpc::Status GetAvailableTransportProfiles(::grpc::ServerContext *context,
                                                             const ::assfire::api::v1::router::GetAvailableTransportProfilesRequest *request,
                                                             ::assfire::api::v1::router::GetAvailableTransportProfilesResponse *response) override;

    private:
        std::shared_ptr<RoutingStrategyProvider> routing_strategies_provider;
        std::shared_ptr<TransportProfileProvider> transport_profiles_provider;
    };
}