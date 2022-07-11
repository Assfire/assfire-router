#pragma once

#include <memory>
#include <vector>
#include <cstdint>
#include <functional>
#include "assfire/router/api/RouteMatrix.hpp"
#include "assfire/router/engine/RoutingStrategy.hpp"
#include "assfire/router/engine/TransportProfile.hpp"

namespace assfire::router
{
    /**
     * \brief This class represents route matrix that is fully initialized on construction using provided calculation function and
     * using provided fallback routing strategy for not indexed routes
     *
     */
    class ImmutableRouteMatrix : public RouteMatrix
    {
    public:
        using RouteInfoSupplier = std::function<RouteInfo(std::size_t, std::size_t)>;

        /**
         * \brief Construct a new ImmutableRouteMatrix object
         *
         * \param origins_count Count of origins to generate matrix for
         * \param destinations_count Count of destinations to generate matrix for
         * \param calculate_route Function to calculate route between i-th origin and j-th destination
         * \param fallback_strategy Strategy to use when calculating routes between not indexed locations
         * \param transport_profile Transport profile associated with this distance matrix. Is passed down to the fallback strategy
         */
        ImmutableRouteMatrix(std::size_t origins_count,
                             std::size_t destinations_count,
                             RouteInfoSupplier calculate_route,
                             std::shared_ptr<RoutingStrategy> fallback_strategy,
                             TransportProfile transport_profile);

        /**
         * \brief Construct a new ImmutableRouteMatrix object without any fallback strategy configured. If this constructor was used to create matrix,
         * any call for not indexed locations will fail with exception
         * 
         * \param origins_count Count of origins to generate matrix for
         * \param destinations_count Count of destinations to generate matrix for
         * \param calculate_route Function to calculate route between i-th origin and j-th destination
         * 
         */
        ImmutableRouteMatrix(std::size_t origins_count,
                             std::size_t destinations_count,
                             RouteInfoSupplier calculate_route);

        virtual RouteInfo get_route_info(GeopointId origin, GeopointId destination) const override;
        virtual RouteInfo::Meters get_distance_meters(GeopointId origin, GeopointId destination) const override;
        virtual RouteInfo::Seconds get_travel_time_seconds(GeopointId origin, GeopointId destination) const override;
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination) const override;
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination) const override;
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination) const override;
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination) const override;
        virtual void sync() const override;

    private:
        void validate_geopoint_id(GeopointId origin, GeopointId destination) const;
        void ensure_strategy_present() const;
        const RouteInfo& retrieve_route_info(GeopointId origin, GeopointId destination) const;

        std::size_t origins_count;
        std::size_t destinations_count;
        TransportProfile transport_profile;
        std::shared_ptr<RoutingStrategy> fallback_strategy;
        std::vector<RouteInfo> data;
    };
}