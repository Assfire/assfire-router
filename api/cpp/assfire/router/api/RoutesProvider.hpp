#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <optional>
#include "Route.hpp"
#include "RouteMatrix.hpp"

namespace assfire::router
{
    /**
     * \brief Id of strategy that should be used to calculate route. Defines routing algorithm/provider and its settings. Strategies themselves are configured at implementation level
     */
    struct RoutingStrategyId
    {
        std::string value;
    };

    /**
     * \brief Id of profile that defines transport specifics like speed, weight, restriction etc. Profiles themselves are configured at implementation level
     */
    struct TransportProfileId
    {
        std::string value;
    };

    /**
     * \brief This class provides routing information for geographical points such as route summaries (distance and travel time) and verbose waypoints path between origins
     * and destinations
     */
    class RoutesProvider
    {
    public:
        using MatrixPtr = std::shared_ptr<RouteMatrix>;
        using WaypointsSupplier = std::function<std::optional<GeoPoint>()>;
        using Waypoints = std::vector<GeoPoint>;

        /**
         * \brief Calculates single route including waypoints using specified strategy and default transport profile
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Route containing summary (distance and travel time) and waypoints. Waypoints precision depends on selected routing strategy
         */
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates single route including waypoints using specified strategy and transport profile
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Route containing summary (distance and travel time) and waypoints. Waypoints precision depends on selected routing strategy
         */
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates single route summary not including waypoints using specified strategy and default transport profile.
         *
         * This method is usually faster than calculate_route() and should be preferred in cases when no waypoints are needed
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Route summary (distance and travel time)
         */
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates single route summary not including waypoints using specified strategy and transport profile.
         *
         * This method is usually faster than calculate_route() and should be preferred in cases when no waypoints are needed
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Route summary (distance and travel time)
         */
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates distance between 2 geo points using specified strategy and default transport profile.
         * 
         * \details
         * Effectively equal to
         * \endcode{.cpp}
         * calculate_route_info(origin, destination, strategy).distance_meters()
         * \endcode
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Distance in meters between origin and destination
         */
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates distance between 2 geo points using specified strategy and transport profile.
         * 
         * \details
         * Effectively equal to
         * \endcode{.cpp}
         * calculate_route_info(origin, destination, strategy, profile).distance_meters()
         * \endcode
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Distance in meters between origin and destination
         */
        virtual RouteInfo::Meters calculate_distance_meters(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates travel time between 2 geo points using specified strategy and default transport profile.
         *
         * \details
         * Effectively equal to
         * \endcode{.cpp}
         * calculate_route_info(origin, destination, strategy).duration_seconds()
         * \endcode
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Travel time in seconds between origin and destination
         */
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates distance between 2 geo points using specified strategy and transport profile.
         *
         * \details
         * Effectively equal to
         * \endcode{.cpp}
         * calculate_route_info(origin, destination, strategy, profile).duration_seconds()
         * \endcode
         *
         * \param origin Origin point
         * \param destination Destination point
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Travel time in seconds between origin and destination
         */
        virtual RouteInfo::Seconds calculate_travel_time_seconds(const GeoPoint &origin, const GeoPoint &destination, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all waypoints using specified strategy and default transport profile.
         *
         * \details This method should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints vector (0..N)
         *
         * Please note that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all waypoints using specified strategy and transport profile.
         *
         * \details This method should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints vector (0..N)
         *
         * Please note that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all waypoints using specified strategy and default transport profile.
         *
         * \details This method should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints stream (0..N)
         *
         * Please note that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * This overload consumes waypoints from a stream and may be used in cases where data aren't available as std::vector.
         * Consuming stops when stream's operator() returns empty optional
         *
         * \param waypoints Stream of waypoints to calculate routes for. Is consumed until empty optional is returned
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all waypoints using specified strategy and transport profile.
         *
         * \details This method should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints stream (0..N)
         *
         * Please note that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * This overload consumes waypoints from a stream and may be used in cases where data aren't available as std::vector.
         * Consuming stops when stream's operator() returns empty optional
         *
         * \param waypoints Stream of waypoints to calculate routes for. Is consumed until empty optional is returned
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)A
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all origins and all destinations using specified strategy and default transport profile.
         *
         * \details This method should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints vector (0..N)
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * Please not that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * \param origins Vector of origins to calculate routes for
         * \param destinations Vector of destinations to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const RoutingStrategyId& strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all origins and all destinations using specified strategy and transport profile.
         *
         * \details This method should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints vector (0..N)
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * Please not that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * \param origins Vector of origins to calculate routes for
         * \param destinations Vector of destinations to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)A
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(const Waypoints &origins, const Waypoints &destinations, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all origins and all destinations using specified strategy and default transport profile.
         *
         * \details This method should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints streams (0..N)
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * Please not that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * This overload consumes waypoints from a stream and may be used in cases where data aren't available as std::vector.
         * Consuming stops when stream's operator() returns empty optional
         *
         * \param origins Stream of origins to calculate routes for
         * \param destinations Stream of destinations to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates matrix containing summaries of routes between all origins and all destinations using specified strategy and transport profile.
         *
         * \details This method Should be used in case routes between points are needed many times (like when solving transport optimization problems).
         * Routes in matrix are addressed by geo point ids, that are assigned in the order waypoints appear in provided waypoints streams (0..N)
         *
         * No filtering or deduplication is applied to the waypoints
         *
         * Please not that depending on implementation matrix can be calculated asynchronously. Returned pointer is guaranteed to be thread-safe
         * and copyable at any moment but blocking may occur on access to matrix elements. To avoid blocking at unpredictable moment, you may use
         * sync() method provided by matrix interface. It will block immediately until whole matrix becomes available
         *
         * This overload consumes waypoints from a stream and may be used in cases where data aren't available as std::vector.
         * Consuming stops when stream's operator() returns empty optional
         *
         * \param origins Stream of origins to calculate routes for
         * \param destinations Stream of destinations to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Thread-safe shared pointer to calculated matrix
         */
        virtual MatrixPtr calculate_route_matrix(WaypointsSupplier origins, WaypointsSupplier destinations, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) const = 0;

        /**
         * \brief Calculates routes (including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and default transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * std::vector<Route> result;
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   result.push_back(calculate_route(waypoints[i], waypoints[j], strategy));
         * }
         * return result;
         * \endcode
         *
         * This method is usually faster than just calling calculate_route() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Vector of routes between adjacent elements of waypoints including verbose subwaypoints between each requested point
         */
        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;

        /**
         * \brief Calculates routes (including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * std::vector<Route> result;
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   result.push_back(calculate_route(waypoints[i], waypoints[j], profile, strategy));
         * }
         * return result;
         * \endcode
         *
         * This method is usually faster than just calling calculate_route() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Vector of routes between adjacent elements of waypoints including verbose subwaypoints between each requested point
         */
        virtual std::vector<Route> calculate_routes_vector(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;

        /**
         * \brief Calculates routes (including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and default transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   consume_route(std::move(calculate_route(waypoints[i], waypoints[j], strategy)));
         * }
         * \endcode
         *
         * This method is usually faster than just calling calculate_route() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param consume_route Function to pass calculated routes to. Routes are passed in same order as waypoints appear in provided list
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         */
        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;

        /**
         * \brief Calculates routes (including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   consume_route(std::move(calculate_route(waypoints[i], waypoints[j], profile, strategy)));
         * }
         * \endcode
         *
         * This method is usually faster than just calling calculate_route() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param consume_route Function to pass calculated routes to. Routes are passed in same order as waypoints appear in provided list
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         */
        virtual void calculate_routes_vector(const Waypoints &waypoints, std::function<void(Route)> consume_route, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;

        /**
         * \brief Calculates route summaries(not including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and default transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * std::vector<RouteInfo> result;
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   result.push_back(calculate_route_info(waypoints[i], waypoints[j], strategy));
         * }
         * return result;
         * \endcode
         *
         * This method is usually faster than just calling calculate_route_info() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         * \return Vector of route summaries (distance and travel times) between adjacent elements of provided waypoints list
         */
        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;

        /**
         * \brief Calculates route summaries(not including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * std::vector<RouteInfo> result;
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   result.push_back(calculate_route_info(waypoints[i], waypoints[j], profile, strategy));
         * }
         * return result;
         * \endcode
         *
         * This method is usually faster than just calling calculate_route_info() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         * \return Vector or route summaries (distance and travel times) between adjacent elements of provided waypoints list
         */
        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;

        /**
         * \brief Calculates route summaries (not including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and default transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   consume_route_info(std::move(calculate_route_info(waypoints[i], waypoints[j], strategy)));
         * }
         * \endcode
         *
         * This method is usually faster than just calling calculate_route_info() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param consume_route_info Function to provide calculated route summaries to. Routes are passed in same order as waypoints appear in provided list
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         *
         */
        virtual void calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;

        /**
         * \brief Calculates route summaries (not including verbose waypoints) between adjacent elements of provided waypoints list using specified strategy and transport profile
         *
         * \details 
         * Effectively equal to
         * \code {.cpp}
         * for(int i = 0; i < waypoints.size() - 1; ++i) {
         *   consume_route_info(std::move(calculate_route_info(waypoints[i], waypoints[j], profile, strategy)));
         * }
         * \endcode
         *
         * This method is usually faster than just calling calculate_route_info() in a loop because of less overhead.
         * For remote implementations this doesn't require a network call for each element, for inprocess implementations internal calculation state may be reused
         * for different elements to reduce total routing time.
         *
         * \param waypoints Vector of waypoints to calculate routes for
         * \param consume_route_info Function to provide calculated route summaries to. Routes are passed in same order as waypoints appear in provided list
         * \param strategy Id of routing strategy to use for routing (possible values depend on implementation)
         * \param profile Id of transport profile to use for routing (possible values depend on implementation)
         *
         */
        virtual std::vector<RouteInfo> calculate_route_infos_vector(const Waypoints &waypoints, std::function<void(RouteInfo)> consume_route_info, const TransportProfileId &profile = TransportProfileId(), const RoutingStrategyId &strategy = RoutingStrategyId()) = 0;
    };
}