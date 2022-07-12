
#pragma once

#include <unordered_map>
#include "RoutingStrategyProvider.hpp"

namespace assfire::router
{
    class BasicRoutingStrategyProvider : public RoutingStrategyProvider
    {
    public:
        static std::string CROWFLIGHT;

        BasicRoutingStrategyProvider();
        std::shared_ptr<RoutingStrategy> get_routing_strategy(const RoutingStrategyId &id) const override;
        const std::vector<RoutingStrategyId>& get_available_strategies() const override;

    private:
        std::unordered_map<std::string, std::shared_ptr<RoutingStrategy>> strategies;
        std::vector<RoutingStrategyId> available_strategies;
    };
}