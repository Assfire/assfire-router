#include "InfinityRoutingStrategy.hpp"

namespace assfire::router
{
    Route InfinityRoutingStrategy::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const
    {
        return Route(calculate_route_info(origin, destination, profile));
    }

    RouteInfo InfinityRoutingStrategy::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const
    {
        return RouteInfo(RouteInfo::INFINITE_DISTANCE, RouteInfo::INFINITE_TRAVEL_TIME);
    }
}