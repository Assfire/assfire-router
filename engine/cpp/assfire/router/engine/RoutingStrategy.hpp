#pragma once

#include <optional>
#include <functional>
#include "assfire/router/api/Route.hpp"
#include "TransportProfile.hpp"

namespace assfire::router
{
    class RoutingStrategy
    {
    public:
        using MatrixPtr = std::shared_ptr<RouteMatrix>;
        using Waypoints = std::vector<GeoPoint>;
        using WaypointsSupplier = std::function<std::optional<GeoPoint>()>;

        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const = 0;
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const = 0;
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const = 0;
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const = 0;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const TransportProfile &profile) const = 0;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfile &profile) const = 0;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfile &profile) const = 0;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfile &profile) const = 0;
        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const TransportProfile &profile) = 0;
        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfile &profile) = 0;
        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfile &profile) = 0;
        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfile &profile) = 0;
    };
}