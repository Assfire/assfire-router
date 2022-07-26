#pragma once

#include <string>

namespace assfire::router {
    /**
     * \brief Id of profile that defines transport specifics like speed, weight,
     * restriction etc. Profiles themselves are configured at implementation
     * level
     */
    class TransportProfileId {
      public:
        TransportProfileId() = default;
        explicit TransportProfileId(const std::string& value) : _value(value) {}
        TransportProfileId(const TransportProfileId& rhs) = default;
        TransportProfileId(TransportProfileId&& rhs)      = default;

        TransportProfileId& operator=(const TransportProfileId& rhs) = default;
        TransportProfileId& operator=(TransportProfileId&& rhs) = default;

        const std::string& value() const {
            return _value;
        }

        bool operator==(const TransportProfileId& rhs) const = default;

      private:
        std::string _value;
    };
} // namespace assfire::router