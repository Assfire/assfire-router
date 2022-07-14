#pragma once

#include "assfire/api/v1/router/router.pb.h"
#include "assfire/router/api/GeoPoint.hpp"
#include "assfire/router/api/RouteInfo.hpp"
#include "assfire/router/api/Route.hpp"

namespace assfire::router
{
    GeoPoint parse_geo_point(const assfire::api::v1::router::GeoPoint &gp)
    {
        return GeoPoint(gp.lat(), gp.lon());
    }

    void to_proto(const GeoPoint &gp, assfire::api::v1::router::GeoPoint *out_result)
    {
        out_result->set_lat(gp.lat());
        out_result->set_lon(gp.lon());
    }

    assfire::api::v1::router::GeoPoint to_proto(const GeoPoint &gp)
    {
        assfire::api::v1::router::GeoPoint result;
        to_proto(gp, &result);
        return result;
    }

    RouteInfo parse_route_info(const assfire::api::v1::router::RouteInfo &ri)
    {
        return RouteInfo(ri.distance_meters(), ri.travel_time_seconds());
    }

    void to_proto(const RouteInfo &ri, assfire::api::v1::router::RouteInfo *out_result)
    {
        out_result->set_distance_meters(ri.distance_meters());
        out_result->set_travel_time_seconds(ri.travel_time_seconds());
    }

    assfire::api::v1::router::RouteInfo to_proto(const RouteInfo &ri)
    {
        assfire::api::v1::router::RouteInfo result;
        to_proto(ri, &result);
        return result;
    }

    Route parse_route(const assfire::api::v1::router::RouteInfo &r)
    {
        Route result(RouteInfo(r.distance_meters(), r.travel_time_seconds()));
        for (const auto &wp : r.waypoints())
        {
            result.add_waypoint(parse_geo_point(wp));
        }
        return result;
    }

    void to_proto(const Route &r, assfire::api::v1::router::RouteInfo *out_result)
    {
        out_result->set_distance_meters(r.distance_meters());
        out_result->set_travel_time_seconds(r.travel_time_seconds());
        for (const auto &wp : r.waypoints())
        {
            to_proto(wp, out_result->add_waypoints());
        }
    }

    assfire::api::v1::router::RouteInfo to_proto(const Route &r)
    {
        assfire::api::v1::router::RouteInfo result;
        to_proto(r, &result);
        return result;
    }
}