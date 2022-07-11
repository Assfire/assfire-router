#include "RouterServiceImpl.hpp"

namespace assfire::router
{
    RouterServiceImpl::RouterServiceImpl(std::unique_ptr<RouterEngine> engine) : engine(std::move(engine))
    {
    }

    grpc::Status RouterServiceImpl::GetRoutesBatch(::grpc::ServerContext *context,
                                                   const ::assfire::api::v1::router::GetRoutesBatchRequest *request,
                                                   ::grpc::ServerWriter<::assfire::api::v1::router::GetRoutesBatchResponse> *writer)
    {
        /*
        [TODO] Auth, quote checks and logging
        std::multimap<grpc::string_ref, grpc::string_ref> metadata = context->client_metadata();
        auto auth = metadata.find("authorization");
        if (auth == metadata.end()) {
            return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED");
        }
        */

        grpc::Status returnValue;
        return returnValue;
    }

    grpc::Status RouterServiceImpl::GetRoutesVector(::grpc::ServerContext *context,
                                                    const ::assfire::api::v1::router::GetRoutesVectorRequest *request,
                                                    ::assfire::api::v1::router::GetRoutesVectorResponse *response)
    {
        /*
        [TODO] Auth, quote checks and logging
        std::multimap<grpc::string_ref, grpc::string_ref> metadata = context->client_metadata();
        auto auth = metadata.find("authorization");
        if (auth == metadata.end()) {
            return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED");
        }
        */

        grpc::Status returnValue;
        return returnValue;
    }

    grpc::Status RouterServiceImpl::GetSingleRoute(::grpc::ServerContext *context,
                                                   const ::assfire::api::v1::router::GetSingleRouteRequest *request,
                                                   ::assfire::api::v1::router::GetSingleRouteResponse *response)
    {
        /*
        [TODO] Auth, quote checks and logging
        std::multimap<grpc::string_ref, grpc::string_ref> metadata = context->client_metadata();
        auto auth = metadata.find("authorization");
        if (auth == metadata.end()) {
            return Status(StatusCode::UNAUTHENTICATED, "UNAUTHORIZED");
        }
        */

        

        grpc::Status returnValue;
        return returnValue;
    }
}