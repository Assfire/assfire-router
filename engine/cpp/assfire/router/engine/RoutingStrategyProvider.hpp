#pragma once

#include <memory>
#include "assfire/router/api/RoutingStrategyId.hpp"
#include "assfire/router/engine/common/RoutingStrategy.hpp"

namespace assfire::router {
    class RoutingStrategyProvider {
    public:
        virtual std::shared_ptr<RoutingStrategy> get_routing_strategy(const RoutingStrategyId& id) const = 0;
        virtual std::vector<RoutingStrategyId> get_available_strategies() const = 0;
    };
}