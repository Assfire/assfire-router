#include "assfire/api/v1/router/router_mock.grpc.pb.h"

#include <iostream>
#include <algorithm>

namespace assfire::router
{
    class GetSingleRouteRequestMatcher
    {
    public:
        using is_gtest_matcher = void;

        explicit GetSingleRouteRequestMatcher(assfire::api::v1::router::GetSingleRouteRequest expected_request) : expected_request(expected_request) {}

        bool MatchAndExplain(const assfire::api::v1::router::GetSingleRouteRequest &request,
                             std::ostream * /* listener */) const
        {
            bool result = request.origin().lat() == expected_request.origin().lat() &&
                          request.origin().lon() == expected_request.origin().lon() &&
                          request.destination().lat() == expected_request.destination().lat() &&
                          request.destination().lon() == expected_request.destination().lon() &&
                          request.routing_strategy() == expected_request.routing_strategy() &&
                          request.transport_profile() == expected_request.transport_profile() &&
                          request.get_waypoints() == expected_request.get_waypoints();

            return result;
        }

        void DescribeTo(std::ostream *os) const
        {
            *os << " equals expected request";
        }

        void DescribeNegationTo(std::ostream *os) const
        {
            *os << " does not equal expected request";
        }

    private:
        assfire::api::v1::router::GetSingleRouteRequest expected_request;
    };

    ::testing::Matcher<const assfire::api::v1::router::GetSingleRouteRequest &> SingleRouteRequestEq(assfire::api::v1::router::GetSingleRouteRequest expected_request)
    {
        return GetSingleRouteRequestMatcher(expected_request);
    }

    class GetRoutesBatchRequestMatcher
    {
    public:
        using is_gtest_matcher = void;

        explicit GetRoutesBatchRequestMatcher(assfire::api::v1::router::GetRoutesBatchRequest expected_request) : expected_request(expected_request) {}

        bool MatchAndExplain(const assfire::api::v1::router::GetRoutesBatchRequest &request,
                             std::ostream * /* listener */) const
        {
            bool result = std::equal(request.origins().begin(), request.origins().end(), expected_request.origins().begin(), expected_request.origins().end(),
                                     [&](const auto &a, const auto &b)
                                     { return a.lat() == b.lat() && a.lon() == b.lon(); }) &&
                          std::equal(request.destinations().begin(), request.destinations().end(), expected_request.destinations().begin(), expected_request.destinations().end(),
                                     [&](const auto &a, const auto &b)
                                     { return a.lat() == b.lat() && a.lon() == b.lon(); }) &&
                          request.routing_strategy() == expected_request.routing_strategy() &&
                          request.transport_profile() == expected_request.transport_profile();

            return result;
        }

        void DescribeTo(std::ostream *os) const
        {
            *os << " equals expected request";
        }

        void DescribeNegationTo(std::ostream *os) const
        {
            *os << " does not equal expected request";
        }

    private:
        assfire::api::v1::router::GetRoutesBatchRequest expected_request;
    };

    ::testing::Matcher<const assfire::api::v1::router::GetRoutesBatchRequest &> RoutesBatchRequestEq(assfire::api::v1::router::GetRoutesBatchRequest expected_request)
    {
        return GetRoutesBatchRequestMatcher(expected_request);
    }

    class GetRoutesVectorRequestMatcher
    {
    public:
        using is_gtest_matcher = void;

        explicit GetRoutesVectorRequestMatcher(assfire::api::v1::router::GetRoutesVectorRequest expected_request) : expected_request(expected_request) {}

        bool MatchAndExplain(const assfire::api::v1::router::GetRoutesVectorRequest &request,
                             std::ostream * /* listener */) const
        {
            bool result = std::equal(request.waypoints().begin(), request.waypoints().end(), expected_request.waypoints().begin(), expected_request.waypoints().end(),
                                     [&](const auto &a, const auto &b)
                                     { return a.lat() == b.lat() && a.lon() == b.lon(); }) &&
                          request.routing_strategy() == expected_request.routing_strategy() &&
                          request.transport_profile() == expected_request.transport_profile() &&
                          request.get_waypoints() == expected_request.get_waypoints();

            return result;
        }

        void DescribeTo(std::ostream *os) const
        {
            *os << " equals expected request";
        }

        void DescribeNegationTo(std::ostream *os) const
        {
            *os << " does not equal expected request";
        }

    private:
        assfire::api::v1::router::GetRoutesVectorRequest expected_request;
    };

    ::testing::Matcher<const assfire::api::v1::router::GetRoutesVectorRequest &> RoutesVectorRequestEq(assfire::api::v1::router::GetRoutesVectorRequest expected_request)
    {
        return GetRoutesVectorRequestMatcher(expected_request);
    }
}