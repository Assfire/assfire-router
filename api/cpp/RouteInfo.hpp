#pragma once

#include <cstdint>
#include <string>

namespace assfire::router
{
    /**
     * \brief This class represents route summary (distance and travel time) between 2 geo points
     */
    class RouteInfo
    {
    public:
        using Meters = double;
        using Seconds = std::int32_t;

        RouteInfo() = default;
        RouteInfo(Meters meters, Seconds seconds) : _meters(meters),
                                                    _seconds(seconds) {}
        RouteInfo(const RouteInfo &rhs) = default;
        RouteInfo(RouteInfo &&rhs) = default;

        Meters distance_meters() const
        {
            return _meters;
        }

        void set_distance_meters(Meters meters)
        {
            this->_meters = meters;
        }

        Seconds duration_seconds() const
        {
            return _seconds;
        }

        void set_duration_seconds(Seconds seconds)
        {
            this->_seconds = seconds;
        }

        RouteInfo &operator=(const RouteInfo &rhs) = default;
        RouteInfo &operator=(RouteInfo &&rhs) = default;
        bool operator==(const RouteInfo &rhs) const = default;
        bool operator!=(const RouteInfo &rhs) const = default;

        RouteInfo operator+(const RouteInfo &rhs) const
        {
            RouteInfo result(*this);
            result += rhs;
            return result;
        }

        RouteInfo &operator+=(const RouteInfo &rhs)
        {
            _meters += rhs._meters;
            _seconds += rhs._seconds;
            return *this;
        }

        RouteInfo operator-(const RouteInfo &rhs) const
        {
            RouteInfo result(*this);
            result -= rhs;
            return result;
        }

        RouteInfo &operator-=(const RouteInfo &rhs)
        {
            _meters -= rhs._meters;
            _seconds -= rhs._seconds;
            return *this;
        }

        RouteInfo operator*(double value)
        {
            RouteInfo result(*this);
            result *= value;
            return result;
        }

        RouteInfo &operator*=(double value)
        {
            _meters *= value;
            _seconds *= value;
            return *this;
        }

        RouteInfo operator/(double value)
        {
            RouteInfo result(*this);
            result /= value;
            return result;
        }

        RouteInfo &operator/=(double value)
        {
            _meters /= value;
            _seconds /= value;
            return *this;
        }

        std::string to_string() const
        {
            std::string result("[");
            result += std::to_string(_meters);
            result += "m, ";
            result += std::to_string(_seconds);
            result += "s]";
            return result;
        }

    private:
        Meters _meters = 0;
        Seconds _seconds = 0;
    };
}