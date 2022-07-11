#pragma once

#include "assfire/router/api/RouteInfo.hpp"

namespace assfire::router
{
    class TransportProfile
    {
    public:
        using MetersPerSecond = RouteInfo::Meters;

        TransportProfile() = default;

        TransportProfile(MetersPerSecond speed_meters_per_second) : _speed(speed_meters_per_second)
        {
        }

        TransportProfile(const TransportProfile& rhs) = default;
        TransportProfile(TransportProfile&& rhs) = default;

        bool operator==(const TransportProfile& rhs) const = default;
        bool operator!=(const TransportProfile& rhs) const = default;

        TransportProfile& operator=(const TransportProfile& rhs) = default;
        TransportProfile& operator=(TransportProfile&& rhs) = default;

        MetersPerSecond speed_meters_per_second() const
        {
            return _speed;
        }

        void set_speed_meters_per_second(MetersPerSecond speed) {
            this->_speed = speed;
        }

        /**
         * \brief Calculates time needed to travel specified distance using represented vehicle
         *
         * \param distance_meters Distance in meters to calculate travel time for
         * \return RouteInfo::Seconds Travel time in seconds needed by the represented vehicle to travel specified distance
         */
        RouteInfo::Seconds calculate_time_to_travel_seconds(RouteInfo::Meters distance_meters) const
        {
            return (RouteInfo::Seconds)(distance_meters / _speed);
        }

    private:
        MetersPerSecond _speed = 0;
    };
}