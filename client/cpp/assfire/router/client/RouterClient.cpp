#include "RouterClient.hpp"

#include "assfire/router/api/proto/ProtoSerialization.hpp"

#include <stdexcept>

using namespace assfire::api::v1::router;

namespace assfire::router
{
    Route RouterClient::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return calculate_route(origin, destination, TransportProfileId(), strategy);
    }

    Route RouterClient::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        GetSingleRouteRequest request;
        to_proto(origin, request.mutable_origin());
        to_proto(destination, request.mutable_destination());
        request.set_routing_strategy(strategy.value);
        request.set_transport_profile(profile.value);
        request.set_get_waypoints(true);

        ::grpc::ClientContext context;

        GetSingleRouteResponse response;
        grpc::Status status = router_stub->GetSingleRoute(&context, request, &response);

        if (!status.ok())
        {
            throw std::runtime_error("gRPC call failed: " + status.error_message());
        }

        return parse_route(response.route_info());
    }

    RouteInfo RouterClient::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return calculate_route_info(origin, destination, TransportProfileId(), strategy);
    }

    RouteInfo RouterClient::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        GetSingleRouteRequest request;
        to_proto(origin, request.mutable_origin());
        to_proto(destination, request.mutable_destination());
        request.set_routing_strategy(strategy.value);
        request.set_transport_profile(profile.value);
        request.set_get_waypoints(false);

        ::grpc::ClientContext context;

        GetSingleRouteResponse response;
        grpc::Status status = router_stub->GetSingleRoute(&context, request, &response);

        if (!status.ok())
        {
            throw std::runtime_error("gRPC call failed: " + status.error_message());
        }

        return parse_route_info(response.route_info());
    }

    RouteInfo::Meters RouterClient::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return calculate_route_info(origin, destination, strategy).distance_meters();
    }

    RouteInfo::Meters RouterClient::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return calculate_route_info(origin, destination, profile, strategy).distance_meters();
    }

    RouteInfo::Seconds RouterClient::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return calculate_route_info(origin, destination, strategy).travel_time_seconds();
    }

    RouteInfo::Seconds RouterClient::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return calculate_route_info(origin, destination, profile, strategy).travel_time_seconds();
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(const Waypoints &waypoints, const RoutingStrategyId &strategy) const
    {
        return calculate_route_matrix(waypoints, TransportProfileId(), strategy);
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return calculate_route_matrix(waypoints, waypoints, profile, strategy);
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(WaypointsSupplier waypoints, const RoutingStrategyId &strategy) const
    {
        return calculate_route_matrix(waypoints, TransportProfileId(), strategy);
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        std::vector<GeoPoint> waypoints_vector;
        while (std::optional<GeoPoint> waypoint = waypoints())
        {
            waypoints_vector.push_back(*waypoint);
        }
        return calculate_route_matrix(waypoints_vector, waypoints_vector, profile);
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const RoutingStrategyId &strategy) const
    {
        return calculate_route_matrix(origins, destinations, TransportProfileId(), strategy);
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return nullptr; // [TODO] Implement
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const RoutingStrategyId &strategy) const
    {
        return calculate_route_matrix(origins, destinations, TransportProfileId(), strategy);
    }

    RouterClient::MatrixPtr RouterClient::calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        std::vector<GeoPoint> origins_vector;
        while (std::optional<GeoPoint> origin = origins())
        {
            origins_vector.push_back(*origin);
        }
        std::vector<GeoPoint> destinations_vector;
        while (std::optional<GeoPoint> destination = destinations())
        {
            destinations_vector.push_back(*destination);
        }
        return calculate_route_matrix(origins_vector, destinations_vector, profile);
    }

    std::vector<Route> RouterClient::calculate_routes_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy)
    {
        return calculate_routes_vector(waypoints, TransportProfileId(), strategy);
    }

    std::vector<Route> RouterClient::calculate_routes_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        std::vector<Route> result;
        result.reserve(waypoints.size() - 1);
        calculate_routes_vector(
            waypoints, [&](Route route)
            { result.emplace_back(std::move(route)); },
            profile, strategy);
        return result;
    }

    void RouterClient::calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const RoutingStrategyId &strategy)
    {
        calculate_routes_vector(waypoints, consume_route, TransportProfileId(), strategy);
    }

    void RouterClient::calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        GetRoutesVectorRequest request;
        for (const auto &wp : waypoints)
        {
            to_proto(wp, request.add_waypoints());
        }
        request.set_routing_strategy(strategy.value);
        request.set_transport_profile(profile.value);
        request.set_get_waypoints(true);

        ::grpc::ClientContext context;

        GetRoutesVectorResponse response;
        grpc::Status status = router_stub->GetRoutesVector(&context, request, &response);

        if (!status.ok())
        {
            throw std::runtime_error("gRPC call failed: " + status.error_message());
        }

        for (const auto &r : response.route_infos())
        {
            consume_route(parse_route(r));
        }
    }

    std::vector<RouteInfo> RouterClient::calculate_route_infos_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy)
    {
        return calculate_route_infos_vector(waypoints, TransportProfileId(), strategy);
    }

    std::vector<RouteInfo> RouterClient::calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        std::vector<RouteInfo> result;
        result.reserve(waypoints.size() - 1);
        calculate_route_infos_vector(
            waypoints, [&](RouteInfo route)
            { result.emplace_back(std::move(route)); },
            profile, strategy);
        return result;
    }

    void RouterClient::calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const RoutingStrategyId &strategy)
    {
        calculate_route_infos_vector(waypoints, consume_route_info, TransportProfileId(), strategy);
    }

    void RouterClient::calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        GetRoutesVectorRequest request;
        for (const auto &wp : waypoints)
        {
            to_proto(wp, request.add_waypoints());
        }
        request.set_routing_strategy(strategy.value);
        request.set_transport_profile(profile.value);
        request.set_get_waypoints(false);

        ::grpc::ClientContext context;

        GetRoutesVectorResponse response;
        grpc::Status status = router_stub->GetRoutesVector(&context, request, &response);

        if (!status.ok())
        {
            throw std::runtime_error("gRPC call failed: " + status.error_message());
        }

        for (const auto &r : response.route_infos())
        {
            consume_route_info(parse_route_info(r));
        }
    }
}