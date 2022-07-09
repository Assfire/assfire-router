#pragma once

#include <memory>
#include "assfire/router/api/RoutesProvider.hpp"
#include "RoutingStrategyProvider.hpp"
#include "TransportProfileProvider.hpp"

namespace assfire::router
{
    class RouterEngine : public RoutesProvider
    {
    public:
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const RoutingStrategyId& strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) override;

        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) override;

        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) override;

        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) override;

    private:
        std::unique_ptr<RoutingStrategyProvider> routing_strategy_provider;
        std::unique_ptr<TransportProfileProvider> transport_profile_provider;
    };
}