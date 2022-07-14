#pragma once

#include <memory>
#include <vector>
#include <cstdint>
#include <functional>
#include <atomic>
#include <mutex>
#include "assfire/router/api/RouteMatrix.hpp"
#include "assfire/router/api/RoutingStrategyId.hpp"
#include "assfire/router/api/TransportProfileId.hpp"
#include "assfire/router/api/RoutesProvider.hpp"

namespace assfire::router
{
    /**
     * \brief This class represents route matrix that is explicitly filled in. Memory is preallocated on creation and then user has to fill matrix using set_route_info() method.
     * After all fields are set, mark_complete() method must be used to finish matrix initialization. 
     * If any get_xxx() call is used before mark_complete() was triggered, this call blocks until some other thread calls mark_complete().
     * For unknown locations delegates calculation to routes_provider.
     */
    class CompletableRouteMatrix : public RouteMatrix
    {
    public:
        /**
         * \brief Construct a new ImmutableRouteMatrix object
         *
         * \param origins_count Count of origins to generate matrix for
         * \param destinations_count Count of destinations to generate matrix for
         * \param routes_provider Routes provider to use when calculating routes between not indexed locations
         * \param transport_profile_id Transport profile associated with this distance matrix. Is passed down to the routes provider
         * \param routing_strategy_id Routing associated with this distance matrix. Is passed down to the routes provider
         */
        CompletableRouteMatrix(std::size_t origins_count,
                             std::size_t destinations_count,
                             const RoutesProvider& routes_provider,
                             TransportProfileId transport_profile_id,
                             RoutingStrategyId routing_strategy_id);

        virtual RouteInfo get_route_info(GeopointId origin, GeopointId destination) const override;
        virtual RouteInfo::Meters get_distance_meters(GeopointId origin, GeopointId destination) const override;
        virtual RouteInfo::Seconds get_travel_time_seconds(GeopointId origin, GeopointId destination) const override;
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination) const override;
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination) const override;
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination) const override;
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination) const override;

        /**
         * \brief If matrix is not yet complete, blocks until mark_complete() is called
         * 
         */
        virtual void sync() const override;

        void set_route_info(GeopointId origin, GeopointId destination, RouteInfo route_info);

        /**
         * \brief Marks matrix as complete - so clients are free to retrieve data
         * 
         */
        void mark_complete();

    private:
        void validate_geopoint_id(GeopointId origin, GeopointId destination) const;
        const RouteInfo& retrieve_route_info(GeopointId origin, GeopointId destination) const;
        RouteInfo& retrieve_route_info(GeopointId origin, GeopointId destination);

        void wait_for_completion() const;

        std::size_t origins_count;
        std::size_t destinations_count;
        TransportProfileId transport_profile_id;
        RoutingStrategyId routing_strategy_id;
        const RoutesProvider& routes_provider;
        std::vector<RouteInfo> data;

        std::atomic_bool is_complete;
        mutable std::condition_variable complete_cv;
        mutable std::mutex cv_lock;
    };
}