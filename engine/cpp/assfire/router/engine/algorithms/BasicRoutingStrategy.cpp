#include "BasicRoutingStrategy.hpp"
#include "assfire/router/engine/matrix/ImmutableRouteMatrix.hpp"

namespace assfire::router
{
    RouteInfo::Meters BasicRoutingStrategy::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const
    {
        return calculate_route_info(origin, destination, profile).distance_meters();
    }

    RouteInfo::Seconds BasicRoutingStrategy::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const
    {
        return calculate_route_info(origin, destination, profile).travel_time_seconds();
    }

    RoutingStrategy::MatrixPtr BasicRoutingStrategy::calculate_route_matrix(const Waypoints &waypoints, const TransportProfile &profile) const
    {
        return calculate_route_matrix(waypoints, waypoints, profile);
    }

    RoutingStrategy::MatrixPtr BasicRoutingStrategy::calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfile &profile) const
    {
        std::vector<GeoPoint> waypoints_vector;
        while (std::optional<GeoPoint> waypoint = waypoints())
        {
            waypoints_vector.push_back(*waypoint);
        }
        return calculate_route_matrix(waypoints_vector, waypoints_vector, profile);
    }

    RoutingStrategy::MatrixPtr BasicRoutingStrategy::calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfile &profile) const
    {
        return std::make_shared<ImmutableRouteMatrix>(
            origins.size(), destinations.size(),
            [&](auto origin, auto destination)
            {
                return calculate_route_info(origins[origin], destinations[destination], profile);
            },
            clone(), profile);
    }

    RoutingStrategy::MatrixPtr BasicRoutingStrategy::calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfile &profile) const
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

    std::vector<Route> BasicRoutingStrategy::calculate_routes_vector(const Waypoints &waypoints, const TransportProfile &profile)
    {
        std::vector<Route> result;
        calculate_routes_vector(
            waypoints, [&](auto route)
            { result.emplace_back(route); },
            profile);
        return result;
    }

    void BasicRoutingStrategy::calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfile &profile)
    {
        for (int i = 0; i < waypoints.size() - 1; ++i)
        {
            consume_route(calculate_route(waypoints[i], waypoints[i + 1], profile));
        }
    }
    
    std::vector<RouteInfo> BasicRoutingStrategy::calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfile &profile)
    {
        std::vector<RouteInfo> result;
        calculate_route_infos_vector(
            waypoints, [&](auto route)
            { result.emplace_back(route); },
            profile);
        return result;
    }
    
    void BasicRoutingStrategy::calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfile &profile)
    {
        for (int i = 0; i < waypoints.size() - 1; ++i)
        {
            consume_route_info(calculate_route_info(waypoints[i], waypoints[i + 1], profile));
        }
    }

}