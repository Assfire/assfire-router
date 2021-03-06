#pragma once

#include <memory>
#include "assfire/api/v1/router/router.grpc.pb.h"
#include "assfire/router/engine/RouterEngine.hpp"

namespace assfire::router
{
    class RouterServiceImpl : public assfire::api::v1::router::RouterService::Service
    {
    public:
        RouterServiceImpl(std::unique_ptr<RouterEngine> engine);

        ::grpc::Status GetSingleRoute(::grpc::ServerContext *context,
                                      const ::assfire::api::v1::router::GetSingleRouteRequest *request,
                                      ::assfire::api::v1::router::GetSingleRouteResponse *response);

        ::grpc::Status GetRoutesVector(::grpc::ServerContext *context,
                                       const ::assfire::api::v1::router::GetRoutesVectorRequest *request,
                                       ::assfire::api::v1::router::GetRoutesVectorResponse *response);

        ::grpc::Status GetRoutesBatch(::grpc::ServerContext *context,
                                      const ::assfire::api::v1::router::GetRoutesBatchRequest *request,
                                      ::grpc::ServerWriter<::assfire::api::v1::router::GetRoutesBatchResponse> *writer);

    private:
        std::unique_ptr<RouterEngine> engine;
    };
}