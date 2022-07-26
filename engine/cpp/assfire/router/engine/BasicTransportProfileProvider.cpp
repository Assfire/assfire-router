#include "BasicTransportProfileProvider.hpp"
#include <stdexcept>

namespace assfire::router
{
    TransportProfile BasicTransportProfileProvider::get_transport_profile(const TransportProfileId &id) const
    {
        if (id.value().empty())
        {
            return TransportProfile();
        }
        else
        {
            auto iter = transport_profiles.find(id.value());
            if (iter != transport_profiles.end())
            {
                return iter->second;
            }
            throw std::invalid_argument("Unsupported transport profile: " + id.value());
        }
    }

    const std::vector<TransportProfileId> &BasicTransportProfileProvider::get_available_profiles() const
    {
        return available_profiles;
    }
}