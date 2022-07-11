#pragma once

#include "assfire/router/api/TransportProfileId.hpp"
#include "assfire/router/engine/common/TransportProfile.hpp"

namespace assfire::router {
    class TransportProfileProvider {
    public:
        virtual TransportProfile get_transport_profile(const TransportProfileId& id) const = 0;
        virtual std::vector<TransportProfileId> get_available_profiles() const = 0;
    };
}