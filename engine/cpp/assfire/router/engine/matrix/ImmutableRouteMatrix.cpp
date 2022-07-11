#include "ImmutableRouteMatrix.hpp"

#include <string>
#include <stdexcept>

namespace assfire::router
{
    namespace
    {
        void initialize_data(std::vector<RouteInfo> &data, std::size_t origins_count, std::size_t destinations_count,
                             ImmutableRouteMatrix::RouteInfoSupplier calculate_route)
        {
            data.resize(origins_count * destinations_count);
            for (int i = 0; i < origins_count; ++i)
            {
                for (int j = 0; j < destinations_count; ++j)
                {
                    data[i * destinations_count + j] = calculate_route(i, j);
                }
            }
        }
    }

    ImmutableRouteMatrix::ImmutableRouteMatrix(std::size_t origins_count,
                                               std::size_t destinations_count,
                                               RouteInfoSupplier calculate_route,
                                               std::shared_ptr<RoutingStrategy> fallback_strategy,
                                               TransportProfile transport_profile) : fallback_strategy(fallback_strategy),
                                                                                     origins_count(origins_count),
                                                                                     destinations_count(destinations_count),
                                                                                     transport_profile(transport_profile)
    {
        initialize_data(data, origins_count, destinations_count, std::move(calculate_route));
    }

    ImmutableRouteMatrix::ImmutableRouteMatrix(std::size_t origins_count,
                                               std::size_t destinations_count,
                                               RouteInfoSupplier calculate_route) : origins_count(origins_count),
                                                                                    destinations_count(destinations_count)
    {
        initialize_data(data, origins_count, destinations_count, std::move(calculate_route));
    }

    RouteInfo ImmutableRouteMatrix::get_route_info(GeopointId origin, GeopointId destination) const
    {
        return retrieve_route_info(origin, destination);
    }

    RouteInfo::Meters ImmutableRouteMatrix::get_distance_meters(GeopointId origin, GeopointId destination) const
    {
        return retrieve_route_info(origin, destination).distance_meters();
    }

    RouteInfo::Seconds ImmutableRouteMatrix::get_travel_time_seconds(GeopointId origin, GeopointId destination) const
    {
        return retrieve_route_info(origin, destination).travel_time_seconds();
    }

    Route ImmutableRouteMatrix::calculate_route(const GeoPoint &origin, const GeoPoint &destination) const
    {
        ensure_strategy_present();
        return fallback_strategy->calculate_route(origin, destination, transport_profile);
    }

    RouteInfo ImmutableRouteMatrix::calculate_route_info(const GeoPoint &origin, const GeoPoint &destination) const
    {
        ensure_strategy_present();
        return fallback_strategy->calculate_route_info(origin, destination, transport_profile);
    }

    RouteInfo::Meters ImmutableRouteMatrix::calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination) const
    {
        ensure_strategy_present();
        return fallback_strategy->calculate_distance_meters(origin, destination, transport_profile);
    }

    RouteInfo::Seconds ImmutableRouteMatrix::calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination) const
    {
        ensure_strategy_present();
        return fallback_strategy->calculate_travel_time_seconds(origin, destination, transport_profile);
    }

    void ImmutableRouteMatrix::validate_geopoint_id(GeopointId origin, GeopointId destination) const
    {
        if (origin < 0 || origin >= origins_count || destination < 0 || destination >= destinations_count)
        {
            throw std::invalid_argument("Invalid geopoint ids: " + std::to_string(origin) + "->" + std::to_string(destination));
        }
    }

    void ImmutableRouteMatrix::ensure_strategy_present() const
    {
        if (!fallback_strategy)
        {
            throw std::runtime_error("Route calculation is requested at matrix API but no strategy was provided");
        }
    }

    const RouteInfo &ImmutableRouteMatrix::retrieve_route_info(GeopointId origin, GeopointId destination) const
    {
        validate_geopoint_id(origin, destination);
        return data[origin * destinations_count + destination];
    }

    void ImmutableRouteMatrix::sync() const
    {
        // No-op for this implementation
    }
}