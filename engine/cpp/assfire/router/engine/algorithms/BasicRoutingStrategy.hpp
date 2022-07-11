#pragma once

#include "assfire/router/engine/common/RoutingStrategy.hpp"

namespace assfire::router
{
    /**
     * \brief This class implements common methods for basic routing strategies only able to calculate single routes (like crowflight, euclidean etc.)
     *
     */
    class BasicRoutingStrategy : public RoutingStrategy
    {
    public:
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const override;
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const override;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const TransportProfile &profile) const override;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfile &profile) const override;
        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfile &profile) const override;
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfile &profile) const override;
        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const TransportProfile &profile) override;
        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfile &profile) override;
        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfile &profile) override;
        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfile &profile) override;

    private:
        /**
         * \brief Derived classes should implement this method to produce a copy of themselves to be passed down to route matrix
         *
         * \return std::shared_ptr<RoutingStrategy> A copy of current strategy
         */
        virtual std::shared_ptr<RoutingStrategy> clone() const = 0;
    };
}
