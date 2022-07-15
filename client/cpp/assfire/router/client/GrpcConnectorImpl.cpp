#include "GrpcConnectorImpl.hpp"

#include <grpcpp/create_channel.h>

using namespace assfire::api::v1::router;

namespace assfire::router
{
    // [TODO] Manage channel lifecycle
    GrpcConnectorImpl::GrpcConnectorImpl(const RouterConnectionSettings &settings) : channel(::grpc::CreateChannel(settings.server_address(), settings.build_credentials())),
                                                                                     router_stub(RouterService::NewStub(channel)),
                                                                                     configuration_stub(ConfigurationService::NewStub(channel))
    {
    }

    GrpcConnectorImpl::RouterServiceStub &GrpcConnectorImpl::get_router_stub()
    {
        return *router_stub;
    }

    GrpcConnectorImpl::ConfigurationServiceStub &GrpcConnectorImpl::get_configuration_stub()
    {
        return *configuration_stub;
    }

}