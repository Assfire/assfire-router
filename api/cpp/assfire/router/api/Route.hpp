#pragma once

#include <vector>
#include "GeoPoint.hpp"
#include "RouteInfo.hpp"

namespace assfire::router
{
    /**
     * \brief This class represents route between 2 geo points. It provides route summary (distance and travel time) and additionally
     * provides a list of waypoints to reach destination from origin. Verbosity of waypoints depends on routing strategy used to 
     * calculate route and varies from just origin and destination to detailed points bound to the real road network. 
     */
    class Route
    {
    public:
        using Waypoints = std::vector<GeoPoint>;

        Route() = default;
        Route(const Route &rhs) = default;
        Route(Route &&rhs) = default;
        Route(const RouteInfo &route_info) : _route_info(route_info)
        {
        }
        Route(RouteInfo &&route_info) : _route_info(std::move(route_info))
        {
        }

        Route(const RouteInfo &route_info, const Waypoints &waypoints) : _route_info(route_info),
                                                                         _waypoints(waypoints)
        {
        }

        Route(RouteInfo &&route_info, Waypoints &&waypoints) : _route_info(std::move(route_info)),
                                                               _waypoints(std::move(waypoints))
        {
        }

        bool operator==(const Route& rhs) const = default;
        bool operator!=(const Route& rhs) const = default;
        Route& operator=(const Route& rhs) = default;
        Route& operator=(Route&& rhs) = default;

        const RouteInfo &summary() const
        {
            return _route_info;
        }

        const Waypoints &waypoints() const
        {
            return _waypoints;
        }

        void set_waypoints(const Waypoints& waypoints) {
            _waypoints = waypoints;
        }

        void set_waypoints(Waypoints&& waypoints) {
            _waypoints = std::move(waypoints);
        }

        void add_waypoint(const GeoPoint& geo_point) {
            _waypoints.push_back(geo_point);
        }

        void add_waypoint(GeoPoint&& geo_point) {
            _waypoints.emplace_back(geo_point);
        }

        void set_route_info(const RouteInfo& route_info) {
            _route_info = route_info;
        }

        void set_route_info(RouteInfo&& route_info) {
            _route_info = std::move(route_info);
        }

        void clear_waypoints() {
            _waypoints.clear();
        }

    private:
        RouteInfo _route_info;
        Waypoints _waypoints;
    };
}