#pragma once

namespace assfire::router {
    /**
     * \brief Id of strategy that should be used to calculate route. Defines
     * routing algorithm/provider and its settings. Strategies themselves are
     * configured at implementation level
     */
    class RoutingStrategyId {
      public:
        RoutingStrategyId() = default;
        explicit RoutingStrategyId(const std::string& value) : _value(value) {}
        RoutingStrategyId(const RoutingStrategyId& rhs) = default;
        RoutingStrategyId(RoutingStrategyId&& rhs)      = default;

        RoutingStrategyId& operator=(const RoutingStrategyId& rhs) = default;
        RoutingStrategyId& operator=(RoutingStrategyId&& rhs) = default;

        const std::string& value() const {
            return _value;
        }

      private:
        std::string _value;
    };
} // namespace assfire::router