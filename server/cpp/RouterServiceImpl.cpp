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
                    origins.emplace_back(request->origins()[ii].lat(), request->origins()[ii].lon());
                }
                for (int jj = j; jj < request->destinations().size() && jj < j + BATCH_SIZE; ++jj)
                {
                    destinations.emplace_back(request->destinations()[jj].lat(), request->destinations()[jj].lon());
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
                        route_info->mutable_route_info()->set_distance_meters(route.distance_meters());
                        route_info->mutable_route_info()->set_travel_time_seconds(route.travel_time_seconds());
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
            waypoints.emplace_back(wp.lat(), wp.lon());
        }
        TransportProfileId transport_profile(request->transport_profile());
        RoutingStrategyId routing_strategy(request->routing_strategy());

        if (request->get_waypoints())
        {
            engine->calculate_routes_vector(
                waypoints, [&](Route route)
                {
                assfire::api::v1::router::RouteInfo* route_info = response->add_route_infos();
                route_info->set_distance_meters(route.summary().distance_meters());
                route_info->set_travel_time_seconds(route.summary().travel_time_seconds());
                for (const GeoPoint &waypoint : route.waypoints())
            {
                assfire::api::v1::router::GeoPoint *point = route_info->add_waypoints();
                point->set_lat(waypoint.lat());
                point->set_lon(waypoint.lon());
            } },
                transport_profile, routing_strategy);
        }
        else
        {
            engine->calculate_route_infos_vector(
                waypoints, [&](RouteInfo route)
                {
                assfire::api::v1::router::RouteInfo* route_info = response->add_route_infos();
                route_info->set_distance_meters(route.distance_meters());
                route_info->set_travel_time_seconds(route.travel_time_seconds()); },
                transport_profile, routing_strategy);
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

        GeoPoint origin(request->origin().lat(), request->origin().lon());
        GeoPoint destination(request->destination().lat(), request->destination().lon());
        TransportProfileId transport_profile(request->transport_profile());
        RoutingStrategyId routing_strategy(request->routing_strategy());

        if (request->get_waypoints())
        {
            Route route = engine->calculate_route(origin, destination, transport_profile, routing_strategy);
            response->mutable_route_info()->set_distance_meters(route.summary().distance_meters());
            response->mutable_route_info()->set_travel_time_seconds(route.summary().travel_time_seconds());
            for (const GeoPoint &waypoint : route.waypoints())
            {
                assfire::api::v1::router::GeoPoint *point = response->mutable_route_info()->add_waypoints();
                point->set_lat(waypoint.lat());
                point->set_lon(waypoint.lon());
            }
        }
        else
        {
            RouteInfo summary = engine->calculate_route_info(origin, destination, transport_profile, routing_strategy);
            response->mutable_route_info()->set_distance_meters(summary.distance_meters());
            response->mutable_route_info()->set_travel_time_seconds(summary.travel_time_seconds());
        }

        return grpc::Status::OK;
    }
}