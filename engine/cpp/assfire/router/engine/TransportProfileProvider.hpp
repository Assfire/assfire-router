#pragma once

#include "assfire/router/api/TransportProfileId.hpp"
#include "TransportProfile.hpp"

namespace assfire::router {
    class TransportProfileProvider {
    public:
        virtual TransportProfile get_transport_profile(const TransportProfileId& id) const = 0;
    };
}