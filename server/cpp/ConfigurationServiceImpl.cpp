#include "ConfigurationServiceImpl.hpp"

namespace assfire::router
{

    ConfigurationServiceImpl::ConfigurationServiceImpl(std::shared_ptr<RoutingStrategyProvider> routing_strategies_provider,
                                                       std::shared_ptr<TransportProfileProvider> transport_profiles_provider)
        : routing_strategies_provider(routing_strategies_provider),
          transport_profiles_provider(transport_profiles_provider)
    {
    }

    ::grpc::Status ConfigurationServiceImpl::GetAvailableStrategies(::grpc::ServerContext *context,
                                                                    const ::assfire::api::v1::router::GetAvailableStrategiesRequest *request,
                                                                    ::assfire::api::v1::router::GetAvailableStrategiesResponse *response)
    {
        for (const RoutingStrategyId &strategy : routing_strategies_provider->get_available_strategies())
        {
            response->add_strategies(strategy.value);
        }

        return ::grpc::Status::OK;
    }

    ::grpc::Status ConfigurationServiceImpl::GetAvailableTransportProfiles(::grpc::ServerContext *context,
                                                                           const ::assfire::api::v1::router::GetAvailableTransportProfilesRequest *request,
                                                                           ::assfire::api::v1::router::GetAvailableTransportProfilesResponse *response)
    {
        for (const TransportProfileId &profile : transport_profiles_provider->get_available_profiles())
        {
            response->add_transport_profiles(profile.value);
        }

        return ::grpc::Status::OK;
    }

}