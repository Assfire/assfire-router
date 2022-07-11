#pragma once

#include "BasicRoutingStrategy.hpp"

namespace assfire::router
{
    /**
     * \brief This class represents utilitary routing strategy that always returns infinity as routing result. It can be used as a fallback strategy
     * for cases when ordinary strategy failed to calculate route as an alternative to throwing exception
     */
    class InfinityRoutingStrategy : public BasicRoutingStrategy
    {
    public:
        virtual Route calculate_route(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const override;
        virtual RouteInfo calculate_route_info(const GeoPoint &origin, const GeoPoint &destination, const TransportProfile &profile) const override;
    };
}