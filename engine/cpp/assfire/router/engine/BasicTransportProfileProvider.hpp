
#pragma once

#include <unordered_map>
#include "TransportProfileProvider.hpp"

namespace assfire::router
{
    class BasicTransportProfileProvider : public TransportProfileProvider
    {
    public:
        TransportProfile get_transport_profile(const TransportProfileId &id) const override;
        const std::vector<TransportProfileId> &get_available_profiles() const override;

    private:
        std::vector<TransportProfileId> available_profiles;
        std::unordered_map<std::string, TransportProfile> transport_profiles;
    };
}