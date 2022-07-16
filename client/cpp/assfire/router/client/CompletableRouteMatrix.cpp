
#include "CompletableRouteMatrix.hpp"

#include <iostream>

using namespace std::chrono_literals;

namespace assfire::router {

    CompletableRouteMatrix::CompletableRouteMatrix(
        std::size_t origins_count, std::size_t destinations_count,
        const RoutesProvider &routes_provider,
        TransportProfileId transport_profile_id,
        RoutingStrategyId routing_strategy_id)
        : origins_count(origins_count),
          destinations_count(destinations_count),
          transport_profile_id(transport_profile_id),
          routing_strategy_id(routing_strategy_id),
          routes_provider(routes_provider),
          data(origins_count * destinations_count),
          is_complete(false) {}

    RouteInfo CompletableRouteMatrix::get_route_info(
        GeopointId origin, GeopointId destination) const {
        wait_for_completion();
        return retrieve_route_info(origin, destination);
    }

    RouteInfo::Meters CompletableRouteMatrix::get_distance_meters(
        GeopointId origin, GeopointId destination) const {
        wait_for_completion();
        return retrieve_route_info(origin, destination).distance_meters();
    }

    RouteInfo::Seconds CompletableRouteMatrix::get_travel_time_seconds(
        GeopointId origin, GeopointId destination) const {
        wait_for_completion();
        return retrieve_route_info(origin, destination).travel_time_seconds();
    }

    Route CompletableRouteMatrix::calculate_route(
        const GeoPoint &origin, const GeoPoint &destination) const {
        return routes_provider.calculate_route(
            origin, destination, transport_profile_id, routing_strategy_id);
    }

    RouteInfo CompletableRouteMatrix::calculate_route_info(
        const GeoPoint &origin, const GeoPoint &destination) const {
        return routes_provider.calculate_route_info(
            origin, destination, transport_profile_id, routing_strategy_id);
    }

    RouteInfo::Meters CompletableRouteMatrix::calculate_distance_meters(
        const GeoPoint &origin, const GeoPoint &destination) const {
        return routes_provider.calculate_distance_meters(
            origin, destination, transport_profile_id, routing_strategy_id);
    }

    RouteInfo::Seconds CompletableRouteMatrix::calculate_travel_time_seconds(
        const GeoPoint &origin, const GeoPoint &destination) const {
        return routes_provider.calculate_travel_time_seconds(
            origin, destination, transport_profile_id, routing_strategy_id);
    }

    void CompletableRouteMatrix::sync() const {
        wait_for_completion();
    }

    void CompletableRouteMatrix::set_route_info(GeopointId origin,
                                                GeopointId destination,
                                                RouteInfo route_info) {
        retrieve_route_info(origin, destination) = std::move(route_info);
    }

    void CompletableRouteMatrix::mark_complete() {
        is_complete = true;
        complete_cv.notify_all();
    }

    void CompletableRouteMatrix::validate_geopoint_id(
        GeopointId origin, GeopointId destination) const {
        if (origin < 0 || origin >= origins_count || destination < 0 ||
            destination >= destinations_count) {
            throw std::invalid_argument(
                "Invalid geopoint ids: " + std::to_string(origin) + "->" +
                std::to_string(destination));
        }
    }

    const RouteInfo &CompletableRouteMatrix::retrieve_route_info(
        GeopointId origin, GeopointId destination) const {
        validate_geopoint_id(origin, destination);
        return data[origin * destinations_count + destination];
    }

    RouteInfo &CompletableRouteMatrix::retrieve_route_info(
        GeopointId origin, GeopointId destination) {
        validate_geopoint_id(origin, destination);
        return data[origin * destinations_count + destination];
    }

    void CompletableRouteMatrix::wait_for_completion() const {
        if (is_complete) {
            return;
        } else {
            std::unique_lock<std::mutex> lck(cv_lock);
            complete_cv.wait_for(lck, 5s, [&] {
                return is_complete.load();
            }); // [TODO] Configurable waiting time
        }
    }
} // namespace assfire::router