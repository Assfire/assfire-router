#include "RouterServiceImpl.hpp"

namespace assfire::router
{
    grpc::Status RouterServiceImpl::GetRoutesBatch(::grpc::ServerContext *context,
                                                   const ::assfire::api::v1::router::GetRoutesBatchRequest *request,
                                                   ::grpc::ServerWriter<::assfire::api::v1::router::GetRoutesBatchResponse> *writer)
    {
        grpc::Status returnValue;
        return returnValue;
    }

    grpc::Status RouterServiceImpl::GetRoutesVector(::grpc::ServerContext *context,
                                                    const ::assfire::api::v1::router::GetRoutesVectorRequest *request,
                                                    ::assfire::api::v1::router::GetRoutesVectorResponse *response)
    {
        grpc::Status returnValue;
        return returnValue;
    }

    grpc::Status RouterServiceImpl::GetSingleRoute(::grpc::ServerContext *context,
                                                   const ::assfire::api::v1::router::GetSingleRouteRequest *request,
                                                   ::assfire::api::v1::router::GetSingleRouteResponse *response)
    {
        grpc::Status returnValue;
        return returnValue;
    }
}