#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include "assfire/router/client/RouterClient.hpp"
#include "GrpcConnectorMock.hpp"
#include "ProtoMatchers.hpp"

using namespace assfire::router;
namespace apiv1 = assfire::api::v1::router;
using namespace testing;

TEST(RouterClientTest, GetSingleRoute) {

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);
    
    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(1).WillOnce(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    RouteInfo route = client.calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
}