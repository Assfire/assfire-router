#pragma once

namespace assfire::router
{
    /**
     * \brief Id of profile that defines transport specifics like speed, weight, restriction etc. Profiles themselves are configured at implementation level
     */
    struct TransportProfileId
    {
        TransportProfileId() = default;
        TransportProfileId(const std::string &value) : value(value) {}

        std::string value;
    };
}