#pragma once

#include "assfire/router/api/Route.hpp"

namespace assfire::router
{
    class RoutingStrategy
    {
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfileId &profile = TransportProfileId()) const = 0;

        virtual std::vector <Route> calculate_routes_vector(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId()) = 0;

        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfileId &profile = TransportProfileId()) = 0;

        virtual std::vector <RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId()) = 0;

        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfileId &profile = TransportProfileId()) = 0;
    };
}