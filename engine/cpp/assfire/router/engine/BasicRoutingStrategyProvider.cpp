
#include "BasicRoutingStrategyProvider.hpp"
#include "algorithms/CrowflightRoutingStrategy.hpp"
#include <stdexcept>

namespace assfire::router
{
    std::string BasicRoutingStrategyProvider::CROWFLIGHT = "Crowflight";

    BasicRoutingStrategyProvider::BasicRoutingStrategyProvider()
    {
        strategies.emplace(CROWFLIGHT, std::make_shared<CrowflightRoutingStrategy>());

        available_strategies.push_back(RoutingStrategyId(CROWFLIGHT));
    }

    std::shared_ptr<RoutingStrategy> BasicRoutingStrategyProvider::get_routing_strategy(const RoutingStrategyId &id) const
    {
        if (id.value().empty())
        {
            return strategies.at(CROWFLIGHT);
        }
        
        auto iter = strategies.find(id.value());
        
        if (iter != strategies.end())
        {
            return iter->second;
        }

        throw std::invalid_argument("Unsupported routing strategy: " + id.value());
    }

    const std::vector<RoutingStrategyId>& BasicRoutingStrategyProvider::get_available_strategies() const
    {
        return available_strategies;
    }
}