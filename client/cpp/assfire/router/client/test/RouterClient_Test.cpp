#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include "assfire/router/client/RouterClient.hpp"
#include "GrpcConnectorMock.hpp"
#include "ProtoMatchers.hpp"

using namespace assfire::router;
namespace apiv1 = assfire::api::v1::router;
using namespace testing;

// *** Copied from /grpcpp/test/mock_stream.h ***
namespace grpc::testing {
    template <class R>
    class MockClientReader : public ::grpc::ClientReaderInterface<R> {
    public:
    MockClientReader() = default;

    /// ClientStreamingInterface
    MOCK_METHOD0_T(Finish, Status());

    /// ReaderInterface
    MOCK_METHOD1_T(NextMessageSize, bool(uint32_t*));
    MOCK_METHOD1_T(Read, bool(R*));

    /// ClientReaderInterface
    MOCK_METHOD0_T(WaitForInitialMetadata, void());
    };
}
// ***

TEST(RouterClientTest, GetSingleRouteInfo)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(3).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    RouteInfo route = client.calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4));
    RouteInfo::Meters distance_meters = client.calculate_distance_meters(GeoPoint(1, 2), GeoPoint(3, 4));
    RouteInfo::Seconds travel_time_seconds = client.calculate_travel_time_seconds(GeoPoint(1, 2), GeoPoint(3, 4));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(distance_meters, 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    EXPECT_EQ(travel_time_seconds, 20);
}

TEST(RouterClientTest, GetSingleRouteInfoWithStrategy)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(3).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    RouteInfo route = client.calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4), RoutingStrategyId("FakeStrategy"));
    RouteInfo::Meters distance_meters = client.calculate_distance_meters(GeoPoint(1, 2), GeoPoint(3, 4), RoutingStrategyId("FakeStrategy"));
    RouteInfo::Seconds travel_time_seconds = client.calculate_travel_time_seconds(GeoPoint(1, 2), GeoPoint(3, 4), RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(distance_meters, 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    EXPECT_EQ(travel_time_seconds, 20);
}

TEST(RouterClientTest, GetSingleRouteInfoWithTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(3).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    RouteInfo route = client.calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"));
    RouteInfo::Meters distance_meters = client.calculate_distance_meters(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"));
    RouteInfo::Seconds travel_time_seconds = client.calculate_travel_time_seconds(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(distance_meters, 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    EXPECT_EQ(travel_time_seconds, 20);
}

TEST(RouterClientTest, GetSingleRouteInfoWithStrategyAndTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(3).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    RouteInfo route = client.calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));
    RouteInfo::Meters distance_meters = client.calculate_distance_meters(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));
    RouteInfo::Seconds travel_time_seconds = client.calculate_travel_time_seconds(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(distance_meters, 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    EXPECT_EQ(travel_time_seconds, 20);
}

TEST(RouterClientTest, GetSingleRoute)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);
    auto wp1 = mocked_response.mutable_route_info()->add_waypoints();
    wp1->set_lat(6);
    wp1->set_lon(7);
    auto wp2 = mocked_response.mutable_route_info()->add_waypoints();
    wp2->set_lat(8);
    wp2->set_lon(9);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    Route route = client.calculate_route(GeoPoint(1, 2), GeoPoint(3, 4));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    ASSERT_THAT(route.waypoints(), ElementsAre(GeoPoint(6, 7), GeoPoint(8, 9)));
}

TEST(RouterClientTest, GetSingleRouteWithStrategy)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);
    auto wp1 = mocked_response.mutable_route_info()->add_waypoints();
    wp1->set_lat(6);
    wp1->set_lon(7);
    auto wp2 = mocked_response.mutable_route_info()->add_waypoints();
    wp2->set_lat(8);
    wp2->set_lon(9);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    Route route = client.calculate_route(GeoPoint(1, 2), GeoPoint(3, 4), RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    ASSERT_THAT(route.waypoints(), ElementsAre(GeoPoint(6, 7), GeoPoint(8, 9)));
}

TEST(RouterClientTest, GetSingleRouteWithTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);
    auto wp1 = mocked_response.mutable_route_info()->add_waypoints();
    wp1->set_lat(6);
    wp1->set_lon(7);
    auto wp2 = mocked_response.mutable_route_info()->add_waypoints();
    wp2->set_lat(8);
    wp2->set_lon(9);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    Route route = client.calculate_route(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    ASSERT_THAT(route.waypoints(), ElementsAre(GeoPoint(6, 7), GeoPoint(8, 9)));
}

TEST(RouterClientTest, GetSingleRouteWithStrategyAndTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetSingleRouteRequest expected_request;
    expected_request.mutable_origin()->set_lat(1);
    expected_request.mutable_origin()->set_lon(2);
    expected_request.mutable_destination()->set_lat(3);
    expected_request.mutable_destination()->set_lon(4);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_response;
    mocked_response.mutable_route_info()->set_distance_meters(10);
    mocked_response.mutable_route_info()->set_travel_time_seconds(20);
    auto wp1 = mocked_response.mutable_route_info()->add_waypoints();
    wp1->set_lat(6);
    wp1->set_lon(7);
    auto wp2 = mocked_response.mutable_route_info()->add_waypoints();
    wp2->set_lat(8);
    wp2->set_lon(9);

    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    Route route = client.calculate_route(GeoPoint(1, 2), GeoPoint(3, 4), TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(route.distance_meters(), 10);
    EXPECT_EQ(route.travel_time_seconds(), 20);
    ASSERT_THAT(route.waypoints(), ElementsAre(GeoPoint(6, 7), GeoPoint(8, 9)));
}

TEST(RouterClientTest, GetRouteInfosVector)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<RouteInfo> routes = client.calculate_route_infos_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)});
    std::vector<RouteInfo> functional_routes;
    client.calculate_route_infos_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
                                        { functional_routes.push_back(r); });

    ASSERT_THAT(routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
    ASSERT_THAT(functional_routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
}

TEST(RouterClientTest, GetRouteInfosVectorWithStrategy)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<RouteInfo> routes = client.calculate_route_infos_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, RoutingStrategyId("FakeStrategy"));
    std::vector<RouteInfo> functional_routes;
    client.calculate_route_infos_vector(
        {GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
        { functional_routes.push_back(r); },
        RoutingStrategyId("FakeStrategy"));

    ASSERT_THAT(routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
    ASSERT_THAT(functional_routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
}

TEST(RouterClientTest, GetRouteInfosVectorWithTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<RouteInfo> routes = client.calculate_route_infos_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, TransportProfileId("FakeProfile"));
    std::vector<RouteInfo> functional_routes;
    client.calculate_route_infos_vector(
        {GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
        { functional_routes.push_back(r); },
        TransportProfileId("FakeProfile"));

    ASSERT_THAT(routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
    ASSERT_THAT(functional_routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
}

TEST(RouterClientTest, GetRouteInfosVectorWithStrategyAndTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(false);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<RouteInfo> routes = client.calculate_route_infos_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));
    std::vector<RouteInfo> functional_routes;
    client.calculate_route_infos_vector(
        {GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
        { functional_routes.push_back(r); },
        TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));

    ASSERT_THAT(routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
    ASSERT_THAT(functional_routes, ElementsAre(RouteInfo(10, 20), RouteInfo(30, 40)));
}

TEST(RouterClientTest, GetRoutesVector)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    auto rwp = ri->add_waypoints();
    rwp->set_lat(10);
    rwp->set_lon(11);
    rwp = ri->add_waypoints();
    rwp->set_lat(12);
    rwp->set_lon(13);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);
    rwp = ri->add_waypoints();
    rwp->set_lat(14);
    rwp->set_lon(15);
    rwp = ri->add_waypoints();
    rwp->set_lat(16);
    rwp->set_lon(17);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<Route> routes = client.calculate_routes_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)});
    std::vector<Route> functional_routes;
    client.calculate_routes_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
                                   { functional_routes.push_back(r); });

    ASSERT_THAT(routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
    ASSERT_THAT(functional_routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
}

TEST(RouterClientTest, GetRoutesVectorWithStrategy)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    auto rwp = ri->add_waypoints();
    rwp->set_lat(10);
    rwp->set_lon(11);
    rwp = ri->add_waypoints();
    rwp->set_lat(12);
    rwp->set_lon(13);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);
    rwp = ri->add_waypoints();
    rwp->set_lat(14);
    rwp->set_lon(15);
    rwp = ri->add_waypoints();
    rwp->set_lat(16);
    rwp->set_lon(17);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<Route> routes = client.calculate_routes_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, RoutingStrategyId("FakeStrategy"));
    std::vector<Route> functional_routes;
    client.calculate_routes_vector(
        {GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
        { functional_routes.push_back(r); },
        RoutingStrategyId("FakeStrategy"));

    ASSERT_THAT(routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
    ASSERT_THAT(functional_routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
}

TEST(RouterClientTest, GetRoutesVectorWithTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    auto rwp = ri->add_waypoints();
    rwp->set_lat(10);
    rwp->set_lon(11);
    rwp = ri->add_waypoints();
    rwp->set_lat(12);
    rwp->set_lon(13);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);
    rwp = ri->add_waypoints();
    rwp->set_lat(14);
    rwp->set_lon(15);
    rwp = ri->add_waypoints();
    rwp->set_lat(16);
    rwp->set_lon(17);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<Route> routes = client.calculate_routes_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, TransportProfileId("FakeProfile"));
    std::vector<Route> functional_routes;
    client.calculate_routes_vector(
        {GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
        { functional_routes.push_back(r); },
        TransportProfileId("FakeProfile"));

    ASSERT_THAT(routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
    ASSERT_THAT(functional_routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
}

TEST(RouterClientTest, GetRoutesVectorWithStrategyAndTransportProfile)
{

    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesVectorRequest expected_request;
    auto wp = expected_request.add_waypoints();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_waypoints();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_waypoints();
    wp->set_lat(5);
    wp->set_lon(6);
    expected_request.set_get_waypoints(true);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("FakeProfile");

    apiv1::GetRoutesVectorResponse mocked_response;
    auto ri = mocked_response.add_route_infos();
    ri->set_distance_meters(10);
    ri->set_travel_time_seconds(20);
    auto rwp = ri->add_waypoints();
    rwp->set_lat(10);
    rwp->set_lon(11);
    rwp = ri->add_waypoints();
    rwp->set_lat(12);
    rwp->set_lon(13);
    ri = mocked_response.add_route_infos();
    ri->set_distance_meters(30);
    ri->set_travel_time_seconds(40);
    rwp = ri->add_waypoints();
    rwp->set_lat(14);
    rwp->set_lon(15);
    rwp = ri->add_waypoints();
    rwp->set_lat(16);
    rwp->set_lon(17);

    EXPECT_CALL(router_stub, GetRoutesVector(_, RoutesVectorRequestEq(expected_request), _)).Times(2).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_response), Return(::grpc::Status::OK)));

    std::vector<Route> routes = client.calculate_routes_vector({GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));
    std::vector<Route> functional_routes;
    client.calculate_routes_vector(
        {GeoPoint(1, 2), GeoPoint(3, 4), GeoPoint(5, 6)}, [&](const auto &r)
        { functional_routes.push_back(r); },
        TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));

    ASSERT_THAT(routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
    ASSERT_THAT(functional_routes, ElementsAre(Route(RouteInfo(10, 20), {GeoPoint(10, 11), GeoPoint(12, 13)}), Route(RouteInfo(30, 40), {GeoPoint(14, 15), GeoPoint(16, 17)})));
}

ACTION_P(build_response, f)
{
    arg0->CopyFrom(f());
}

TEST(RouterClientTest, GetRoutesMatrix)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(5);
    wp->set_lon(6);
    wp = expected_request.add_destinations();
    wp->set_lat(7);
    wp->set_lon(8);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("");
    expected_single_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> origins{GeoPoint(1, 2), GeoPoint(3, 4)};
    std::vector<GeoPoint> destinations{GeoPoint(5, 6), GeoPoint(7, 8)};
    auto matrix = client.calculate_route_matrix(origins, destinations);

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto origin_iter = origins.begin();
    auto destination_iter = destinations.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return origin_iter == origins.end() ? std::nullopt : std::make_optional(*origin_iter++); },
                                           [&]()
                                           { return destination_iter == destinations.end() ? std::nullopt : std::make_optional(*destination_iter++); });
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}

TEST(RouterClientTest, GetRoutesMatrixWithStrategy)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(5);
    wp->set_lon(6);
    wp = expected_request.add_destinations();
    wp->set_lat(7);
    wp->set_lon(8);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("FakeStrategy");
    expected_single_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> origins{GeoPoint(1, 2), GeoPoint(3, 4)};
    std::vector<GeoPoint> destinations{GeoPoint(5, 6), GeoPoint(7, 8)};
    auto matrix = client.calculate_route_matrix(origins, destinations, RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto origin_iter = origins.begin();
    auto destination_iter = destinations.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return origin_iter == origins.end() ? std::nullopt : std::make_optional(*origin_iter++); },
                                           [&]()
                                           { return destination_iter == destinations.end() ? std::nullopt : std::make_optional(*destination_iter++); },
                                           RoutingStrategyId("FakeStrategy"));
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}

TEST(RouterClientTest, GetRoutesMatrixWithTransportProfile)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(5);
    wp->set_lon(6);
    wp = expected_request.add_destinations();
    wp->set_lat(7);
    wp->set_lon(8);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("FakeProfile");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("");
    expected_single_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> origins{GeoPoint(1, 2), GeoPoint(3, 4)};
    std::vector<GeoPoint> destinations{GeoPoint(5, 6), GeoPoint(7, 8)};
    auto matrix = client.calculate_route_matrix(origins, destinations, TransportProfileId("FakeProfile"));

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto origin_iter = origins.begin();
    auto destination_iter = destinations.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return origin_iter == origins.end() ? std::nullopt : std::make_optional(*origin_iter++); },
                                           [&]()
                                           { return destination_iter == destinations.end() ? std::nullopt : std::make_optional(*destination_iter++); },
                                           TransportProfileId("FakeProfile"));
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}

TEST(RouterClientTest, GetRoutesMatrixWithStrategyAndTransportProfile)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(5);
    wp->set_lon(6);
    wp = expected_request.add_destinations();
    wp->set_lat(7);
    wp->set_lon(8);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("FakeProfile");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("FakeStrategy");
    expected_single_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> origins{GeoPoint(1, 2), GeoPoint(3, 4)};
    std::vector<GeoPoint> destinations{GeoPoint(5, 6), GeoPoint(7, 8)};
    auto matrix = client.calculate_route_matrix(origins, destinations, TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto origin_iter = origins.begin();
    auto destination_iter = destinations.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return origin_iter == origins.end() ? std::nullopt : std::make_optional(*origin_iter++); },
                                           [&]()
                                           { return destination_iter == destinations.end() ? std::nullopt : std::make_optional(*destination_iter++); },
                                           TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}

TEST(RouterClientTest, GetRoutesMatrixEqualOriginsAndDestinations)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_destinations();
    wp->set_lat(3);
    wp->set_lon(4);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("");
    expected_single_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> waypoints{GeoPoint(1, 2), GeoPoint(3, 4)};
    auto matrix = client.calculate_route_matrix(waypoints);

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto waypoints_iter = waypoints.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return waypoints_iter == waypoints.end() ? std::nullopt : std::make_optional(*waypoints_iter++); });
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}

TEST(RouterClientTest, GetRoutesMatrixEqualOriginsAndDestinationsWithStrategy)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_destinations();
    wp->set_lat(3);
    wp->set_lon(4);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("FakeStrategy");
    expected_single_request.set_transport_profile("");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> waypoints{GeoPoint(1, 2), GeoPoint(3, 4)};
    auto matrix = client.calculate_route_matrix(waypoints, RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto waypoints_iter = waypoints.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return waypoints_iter == waypoints.end() ? std::nullopt : std::make_optional(*waypoints_iter++); },
                                           RoutingStrategyId("FakeStrategy"));
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}

TEST(RouterClientTest, GetRoutesMatrixEqualOriginsAndDestinationsWithTransportProfile)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_destinations();
    wp->set_lat(3);
    wp->set_lon(4);
    expected_request.set_routing_strategy("");
    expected_request.set_transport_profile("FakeProfile");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("");
    expected_single_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> waypoints{GeoPoint(1, 2), GeoPoint(3, 4)};
    auto matrix = client.calculate_route_matrix(waypoints, TransportProfileId("FakeProfile"));

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto waypoints_iter = waypoints.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return waypoints_iter == waypoints.end() ? std::nullopt : std::make_optional(*waypoints_iter++); },
                                           TransportProfileId("FakeProfile"));
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}

TEST(RouterClientTest, GetRoutesMatrixEqualOriginsAndDestinationsWithStrategyAndTransportProfile)
{
    apiv1::MockRouterServiceStub router_stub;
    apiv1::MockConfigurationServiceStub configuration_stub;
    std::shared_ptr<GrpcConnector> connector = std::make_shared<GrpcConnectorMock>(router_stub, configuration_stub);
    RouterClient client(connector);

    apiv1::GetRoutesBatchRequest expected_request;
    auto wp = expected_request.add_origins();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_origins();
    wp->set_lat(3);
    wp->set_lon(4);
    wp = expected_request.add_destinations();
    wp->set_lat(1);
    wp->set_lon(2);
    wp = expected_request.add_destinations();
    wp->set_lat(3);
    wp->set_lon(4);
    expected_request.set_routing_strategy("FakeStrategy");
    expected_request.set_transport_profile("FakeProfile");

    auto build_first_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(0);
        iri->set_destination_id(1);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(10);
        ri->set_travel_time_seconds(20);
        return response;
    };

    auto build_second_response = []
    {
        apiv1::GetRoutesBatchResponse response;
        auto iri = response.add_route_infos();
        iri->set_origin_id(1);
        iri->set_destination_id(0);
        auto ri = iri->mutable_route_info();
        ri->set_distance_meters(30);
        ri->set_travel_time_seconds(40);
        iri = response.add_route_infos();

        iri->set_origin_id(1);
        iri->set_destination_id(1);
        ri = iri->mutable_route_info();
        ri->set_distance_meters(50);
        ri->set_travel_time_seconds(60);
        return response;
    };

    auto reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    apiv1::GetSingleRouteRequest expected_single_request;
    expected_single_request.mutable_origin()->set_lat(1);
    expected_single_request.mutable_origin()->set_lon(2);
    expected_single_request.mutable_destination()->set_lat(3);
    expected_single_request.mutable_destination()->set_lon(4);
    expected_single_request.set_get_waypoints(false);
    expected_single_request.set_routing_strategy("FakeStrategy");
    expected_single_request.set_transport_profile("FakeProfile");

    apiv1::GetSingleRouteResponse mocked_single_response;
    mocked_single_response.mutable_route_info()->set_distance_meters(10);
    mocked_single_response.mutable_route_info()->set_travel_time_seconds(20);

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));
    EXPECT_CALL(router_stub, GetSingleRoute(_, SingleRouteRequestEq(expected_single_request), _)).Times(1).WillRepeatedly(DoAll(SetArgPointee<2>(mocked_single_response), Return(::grpc::Status::OK)));

    std::vector<GeoPoint> waypoints{GeoPoint(1, 2), GeoPoint(3, 4)};
    auto matrix = client.calculate_route_matrix(waypoints, TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));

    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    reader = new grpc::testing::MockClientReader<apiv1::GetRoutesBatchResponse>();

    EXPECT_CALL(router_stub, GetRoutesBatchRaw(_, RoutesBatchRequestEq(expected_request))).Times(1).WillOnce(Return(reader));

    EXPECT_CALL(*reader, Read(_))
        .WillOnce(DoAll(WithArg<0>(build_response(build_first_response)), Return(true)))
        .WillOnce(DoAll(WithArg<0>(build_response(build_second_response)), Return(true)))
        .WillOnce(Return(false));

    EXPECT_CALL(*reader, Finish())
        .WillOnce(Return(::grpc::Status::OK));

    auto waypoints_iter = waypoints.begin();
    matrix = client.calculate_route_matrix([&]()
                                           { return waypoints_iter == waypoints.end() ? std::nullopt : std::make_optional(*waypoints_iter++); },
                                           TransportProfileId("FakeProfile"), RoutingStrategyId("FakeStrategy"));
    EXPECT_EQ(matrix->get_route_info(0, 1), RouteInfo(10, 20));
    EXPECT_EQ(matrix->get_route_info(0, 0), RouteInfo());
    EXPECT_EQ(matrix->get_route_info(1, 0), RouteInfo(30, 40));
    EXPECT_EQ(matrix->get_route_info(1, 1), RouteInfo(50, 60));

    EXPECT_EQ(matrix->calculate_route_info(GeoPoint(1, 2), GeoPoint(3, 4)), RouteInfo(10, 20));
}
