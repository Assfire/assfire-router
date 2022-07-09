#pragma once

namespace assfire::router
{
/**
 * \brief Id of strategy that should be used to calculate route. Defines routing algorithm/provider and its settings. Strategies themselves are configured at implementation level
 */
    struct RoutingStrategyId
    {
        std::string value;
    };
}