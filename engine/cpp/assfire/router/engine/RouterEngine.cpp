#include "RouterEngine.hpp"

namespace assfire::router
{
    RouterEngine::RouterEngine(std::shared_ptr<RoutingStrategyProvider> routing_strategy_provider, std::shared_ptr<TransportProfileProvider> transport_profile_provider)
        : routing_strategy_provider(routing_strategy_provider),
          transport_profile_provider(transport_profile_provider)
    {
    }

    Route RouterEngine::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route(origin, destination, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    Route RouterEngine::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    RouteInfo RouterEngine::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_info(origin, destination, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    RouteInfo RouterEngine::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_info(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    RouteInfo::Meters RouterEngine::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_distance_meters(origin, destination, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    RouteInfo::Meters RouterEngine::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_distance_meters(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    RouteInfo::Seconds RouterEngine::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_travel_time_seconds(origin, destination, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    RouteInfo::Seconds RouterEngine::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_travel_time_seconds(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &waypoints, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier waypoints, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations, transport_profile_provider->get_transport_profile(profile));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    RouterEngine::MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations, transport_profile_provider->get_transport_profile(profile));
    }

    std::vector<Route> RouterEngine::calculate_routes_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    std::vector<Route> RouterEngine::calculate_routes_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    void RouterEngine::calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints, consume_route, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    void RouterEngine::calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints, consume_route, transport_profile_provider->get_transport_profile(profile));
    }

    std::vector<RouteInfo> RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    std::vector<RouteInfo> RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    void RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints, consume_route_info, transport_profile_provider->get_transport_profile(TransportProfileId()));
    }

    void RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints, consume_route_info, transport_profile_provider->get_transport_profile(profile));
    }
}