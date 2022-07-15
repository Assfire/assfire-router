#pragma once

#include <memory>
#include <vector>
#include "assfire/router/api/RoutesProvider.hpp"
#include "GrpcConnector.hpp"

namespace assfire::router
{
    class RouterClient : public RoutesProvider
    {
    public:
        RouterClient(std::shared_ptr<GrpcConnector> grpc_connector);

        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const RoutingStrategyId& strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) const override;

        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) override;

        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) override;

        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) override;

        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const RoutingStrategyId &strategy = RoutingStrategyId()) override;
        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfileId &profile, const RoutingStrategyId &strategy = RoutingStrategyId()) override;

        std::vector<RoutingStrategyId> retrieve_available_routing_strategies() const;
        std::vector<TransportProfileId> retrieve_available_transport_profiles() const;

    private:
        mutable std::shared_ptr<GrpcConnector> grpc_connector;
    };
}