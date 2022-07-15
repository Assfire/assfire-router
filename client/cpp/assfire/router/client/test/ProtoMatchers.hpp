#include "assfire/api/v1/router/router_mock.grpc.pb.h"

#include <iostream>

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
        assfire::api::v1::router::GetSingleRouteRequest expected_request;
    };

    ::testing::Matcher<const assfire::api::v1::router::GetSingleRouteRequest &> SingleRouteRequestEq(assfire::api::v1::router::GetSingleRouteRequest expected_request)
    {
        return GetSingleRouteRequestMatcher(expected_request);
    }
}