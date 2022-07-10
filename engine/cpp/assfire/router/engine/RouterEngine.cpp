#include "RouterEngine.hpp"

namespace assfire::router
{
    RouterEngine::RouterEngine(std::unique_ptr <RoutingStrategyProvider> routingStrategyProvider, std::unique_ptr <TransportProfileProvider> transportProfileProvider)
            : routing_strategy_provider(std::move(routingStrategyProvider)),
              transport_profile_provider(std::move(transportProfileProvider))
    {}

    Route RouterEngine::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route(origin, destination);
    }

    Route RouterEngine::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    RouteInfo RouterEngine::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_info(origin, destination);
    }

    RouteInfo RouterEngine::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_info(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    RouteInfo::Meters RouterEngine::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_distance_meters(origin, destination);
    }

    RouteInfo::Meters RouterEngine::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_distance_meters(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    RouteInfo::Seconds RouterEngine::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_travel_time_seconds(origin, destination);
    }

    RouteInfo::Seconds RouterEngine::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_travel_time_seconds(origin, destination, transport_profile_provider->get_transport_profile(profile));
    }

    MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &waypoints, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints);
    }

    MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier waypoints, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints);
    }

    MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations);
    }

    MatrixPtr RouterEngine::calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations, transport_profile_provider->get_transport_profile(profile));
    }

    MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations);
    }

    MatrixPtr RouterEngine::calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfileId &profile, const RoutingStrategyId &strategy) const
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_matrix(origins, destinations, transport_profile_provider->get_transport_profile(profile));
    }

    std::vector <Route> RouterEngine::calculate_routes_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints);
    }

    std::vector <Route> RouterEngine::calculate_routes_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    void RouterEngine::calculate_routes_vector(const Waypoints &waypoints, std::function<(void) Route> consume_route, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints, consume_route);
    }

    void RouterEngine::calculate_routes_vector(const Waypoints &waypoints, std::function<(void) Route> consume_route, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_routes_vector(waypoints, consume_route, transport_profile_provider->get_transport_profile(profile));
    }

    std::vector <RouteInfo> RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints);
    }

    std::vector <RouteInfo> RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints, transport_profile_provider->get_transport_profile(profile));
    }

    void RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, std::function<(void) RouteInfo> consume_route_info, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints, consume_route_info);
    }

    void RouterEngine::calculate_route_infos_vector(const Waypoints &waypoints, std::function<(void) RouteInfo> consume_route_info, const TransportProfileId &profile, const RoutingStrategyId &strategy)
    {
        return routing_strategy_provider->get_routing_strategy(strategy)->calculate_route_infos_vector(waypoints, consume_route_info, transport_profile_provider->get_transport_profile(profile));
    }
}