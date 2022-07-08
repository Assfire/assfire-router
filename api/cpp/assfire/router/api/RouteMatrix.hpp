#pragma once

#include <cstdint>
#include "Route.hpp"

namespace assfire::router
{
    /**
     * \brief This class provides routing information for pre-indexed geographical points such as route summaries (distance and travel time) and verbose waypoints path between origins
     * and destinations.
     *
     * \details Please note that only route summaries may be retrieved using fast pre-indexed locations.
     * 
     * Should be used in scenarios where routes between same points are used many times such as when solving transport optimization problems.
     * Implementations of this class provide faster route lookups using indices defined on matrix creation and may include multiple caching layers to speedup
     * routes retrieval.
     *
     * Matrix is always created for single transport profile and with single routing strategy. To work with different profiles / strategies, separate matrix
     * must be calculated for each of their desired combinations
     *
     * This class doesn't provide any means to perform mapping between geo points and their indices so this is a reponsibility of class users to maintain such mapping
     * in case of need
     *
     * For convenience, this class also provides non-cached calculation methods to calculate routes for waypoints that were not known at matrix creation time
     * (e.g. calculated average of multiple points)
     *
     * Implementaton may include blocking and/or non-blocking asynchronous calculations, so to avoid possible unwanted freezes during heavy calculations
     * (e.g. to not break calculation metrics), a sync() method is provided that blocks immediately until whole matrix is available (and it also triggers
     * immediate matrix calculation for lazy implementations)
     */
    class RouteMatrix
    {
    public:
        using GeopointId = std::uint32_t;

       /**
         * \brief Retrieves single route summary between speciifed pre-indexed locations
         *
         * \param origin Id of origin location
         * \param destination Id of destination location
         *
         * \return Route summary (distance and travel time) between specified origin and destination
         */
        virtual RouteInfo get_route_info(GeopointId origin, GeopointId destination) const = 0;

        /**
         * \brief Retrieves distance between speciifed pre-indexed locations
         *
         * \param origin Id of origin location
         * \param destination Id of destination location
         *
         * \return Distance in meters between specified origin and destination
         */
        virtual RouteInfo::Meters get_distance_meters(GeopointId origin, GeopointId destination) const = 0;

        /**
         * \brief Retrieves travel time between speciifed pre-indexed locations
         *
         * \param origin Id of origin location
         * \param destination Id of destination location
         *
         * \return Travel time in seconds between specified origin and destination
         */
        virtual RouteInfo::Seconds get_travel_time_seconds(GeopointId origin, GeopointId destination) const = 0;

        /**
         * \brief Calculates route (including waypoints) between origin and destination 
         *
         * \details This method is provided for convenience to be able to use matrix pointer as routes provider for locations
         * that were unknown at the moment of matrix creation (e.g. calculated locations like weighted point or smth similar).
         * 
         * \param origin Origin location
         * \param destination Destination location
         *
         * \return Route with verbose waypoints between origin and destination
         */
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination) const = 0;

        /**
         * \brief Calculates route summary (not including waypoints) between origin and destination 
         *
         * \details This method is provided for convenience to be able to use matrix pointer as routes provider for locations
         * that were unknown at the moment of matrix creation (e.g. calculated locations like weighted point or smth similar).
         * 
         * For known pre-indexed locations this method is usually slower than the one taking location ids as arguments
         * 
         * \param origin Origin location
         * \param destination Destination location
         *
         * \return Route summary (distance and travel time) between specified origin and destination
         */
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination) const = 0;

        /**
         * \brief Calculates distance between origin and destination 
         *
         * \details This method is provided for convenience to be able to use matrix pointer as routes provider for locations
         * that were unknown at the moment of matrix creation (e.g. calculated locations like weighted point or smth similar).
         * 
         * For known pre-indexed locations this method is usually slower than the one taking location ids as arguments
         * 
         * \param origin Origin location
         * \param destination Destination location
         *
         * \return Distance in meters between specified origin and destination
         */
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination) const = 0;

        /**
         * \brief Calculates travel time between origin and destination 
         *
         * \details This method is provided for convenience to be able to use matrix pointer as routes provider for locations
         * that were unknown at the moment of matrix creation (e.g. calculated locations like weighted point or smth similar).
         * 
         * For known pre-indexed locations this method is usually slower than the one taking location ids as arguments
         * 
         * \param origin Origin location
         * \param destination Destination location
         *
         * \return Travel time in seconds between specified origin and destination
         */
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination) const = 0;

        /**
         * \brief Triggers immediate matrix calculation (if not yet started / done) and blocks until whole matrix is available
         *
         * \details Some implementations may provide asynchronous background matrix calculations with implicit blocking on trying to access not yet calculated element.
         * This may be a problem in cases where no unexpected latency increase is desired (e.g. when measuring optimization algorithm calculation time).
         * 
         * This method allows to eagerly trigger time-consuming matrix calculations at a predictable moment.
         * 
         * \param origin Origin location
         * \param destination Destination location
         *
         * \return Distance in meters between specified origin and destination
         */
        virtual void sync() const = 0;
    };
}