#include "RouterServiceImpl.hpp"

#include "assfire/router/api/proto/ProtoSerialization.hpp"

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

        TransportProfileId transport_profile(request->transport_profile());
        RoutingStrategyId routing_strategy(request->routing_strategy());

        const int BATCH_SIZE = 10;

        std::vector<GeoPoint> origins;
        std::vector<GeoPoint> destinations;
        for (int i = 0; i < request->origins().size(); i += BATCH_SIZE)
        {
            for (int j = 0; j < request->destinations().size(); j += BATCH_SIZE)
            {

                for (int ii = i; ii < request->origins().size() && ii < i + BATCH_SIZE; ++ii)
                {
                    origins.emplace_back(parse_geo_point(request->origins()[ii]));
                }
                for (int jj = j; jj < request->destinations().size() && jj < j + BATCH_SIZE; ++jj)
                {
                    destinations.emplace_back(parse_geo_point(request->destinations()[jj]));
                }

                RouterEngine::MatrixPtr matrix = engine->calculate_route_matrix(origins, destinations, transport_profile, routing_strategy);

                assfire::api::v1::router::GetRoutesBatchResponse response;
                for (int ii = i; ii < request->origins().size() && ii < i + BATCH_SIZE; ++ii)
                {
                    for (int jj = j; jj < request->destinations().size() && jj < j + BATCH_SIZE; ++jj)
                    {
                        RouteInfo route = matrix->get_route_info(ii - i, jj - j);
                        assfire::api::v1::router::IndexedRouteInfo *route_info = response.add_route_infos();
                        route_info->set_origin_id(ii);
                        route_info->set_destination_id(jj);
                        to_proto(route, route_info->mutable_route_info());
                    }
                }
                writer->Write(response); // [TODO] writeLast?

                origins.clear();
                destinations.clear();
            }
        }

        return grpc::Status::OK;
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

        std::vector<GeoPoint> waypoints;
        for (const assfire::api::v1::router::GeoPoint &wp : request->waypoints())
        {
            waypoints.emplace_back(parse_geo_point(wp));
        }
        TransportProfileId transport_profile(request->transport_profile());
        RoutingStrategyId routing_strategy(request->routing_strategy());

        if (request->get_waypoints())
        {
            engine->calculate_routes_vector(
                waypoints, [&](Route route)
                { to_proto(route, response->add_route_infos()); },
                transport_profile,
                routing_strategy);
        }
        else
        {
            engine->calculate_route_infos_vector(
                waypoints, [&](RouteInfo route)
                { to_proto(route, response->add_route_infos()); },
                transport_profile,
                routing_strategy);
        }

        return grpc::Status::OK;
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

        GeoPoint origin = parse_geo_point(request->origin());
        GeoPoint destination = parse_geo_point(request->destination());
        TransportProfileId transport_profile(request->transport_profile());
        RoutingStrategyId routing_strategy(request->routing_strategy());

        if (request->get_waypoints())
        {
            Route route = engine->calculate_route(origin, destination, transport_profile, routing_strategy);
            to_proto(route, response->mutable_route_info());
        }
        else
        {
            RouteInfo summary = engine->calculate_route_info(origin, destination, transport_profile, routing_strategy);
            to_proto(summary, response->mutable_route_info());
        }

        return grpc::Status::OK;
    }
}