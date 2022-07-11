#pragma once

#include "BasicRoutingStrategy.hpp"

namespace assfire::router
{
    class CrowflightRoutingStrategy : public BasicRoutingStrategy
    {
    public:
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const override;
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const override;
        virtual std::shared_ptr<RoutingStrategy> clone() const override;
    };
}