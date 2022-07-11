#include "CrowflightRoutingStrategy.hpp"
#include "CrowflightCalculator.hpp"

namespace assfire::router
{
    Route CrowflightRoutingStrategy::calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const
    {
        return Route(calculate_route_info(origin, destination, profile));
    }

    RouteInfo CrowflightRoutingStrategy::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const
    {
        // [TODO - Metrics, Logging]

        if (origin == destination)
        {
            return RouteInfo();
        }

        RouteInfo::Meters distance_meters = CrowflightCalculator()(origin.lat_double(), origin.lon_double(),
                                                                   destination.lat_double(), destination.lon_double());
        RouteInfo::Seconds travel_time_seconds = profile.calculate_time_to_travel_seconds(distance_meters);

        return RouteInfo(distance_meters, travel_time_seconds);
    }

    std::shared_ptr<RoutingStrategy> CrowflightRoutingStrategy::clone() const
    {
        return std::make_shared<CrowflightRoutingStrategy>();
    }
}