#pragma once

#include <memory>
#include "assfire/router/api/RoutingStrategyId.hpp"
#include "assfire/router/engine/common/RoutingStrategy.hpp"

namespace assfire::router {
    /**
     * \brief This class provides implementations of routing strategies base on identifier. 
     * Implementations can use hardcoded lists, databases, network sources etc. to retrieve data needed to construct strategies
     */
    class RoutingStrategyProvider {
    public:
        /**
         * \brief Returns routing strategy associated with passed id. When no strategy with such id is present, behavior is implementation-defined
         * 
         * \param id Identifier associated with requested strategy
         * 
         * \return std::shared_ptr<RoutingStrategy> Ready to use routing strategy
         */
        virtual std::shared_ptr<RoutingStrategy> get_routing_strategy(const RoutingStrategyId& id) const = 0;

        /**
         * \brief Returns list of valid routing strategy identifiers for this provider
         * 
         * @return std::vector<RoutingStrategyId> List of valid routing strategy identifies for this provider
         */
        virtual const std::vector<RoutingStrategyId>& get_available_strategies() const = 0;
    };
}