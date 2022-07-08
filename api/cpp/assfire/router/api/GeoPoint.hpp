#pragma once

#include <cstdint>
#include <string>

namespace assfire::router
{
    /**
     * \brief This class represents geographic location encoded by latitude and longitude expressed in fixed point integer format with 6 decimal points
     * i.e. coordinates (53.3456, 65.23456) are represented as (53345600, 65234560). 
     */
    class GeoPoint
    {
    public:
        using FixedPointCoordinate = std::int32_t;

        GeoPoint() = default;
        GeoPoint(FixedPointCoordinate lat, FixedPointCoordinate lon) : _lat(lat),
                                                                       _lon(lon) {}
        GeoPoint(const GeoPoint &rhs) = default;
        GeoPoint(GeoPoint &&rhs) = default;

        GeoPoint operator+(const GeoPoint &rhs) const
        {
            GeoPoint result(*this);
            result += rhs;
            return result;
        }

        GeoPoint &operator+=(const GeoPoint &rhs)
        {
            _lat += rhs._lat;
            _lon += rhs._lon;
            return *this;
        }

        GeoPoint operator-(const GeoPoint &rhs) const
        {
            GeoPoint result(*this);
            result -= rhs;
            return result;
        }

        GeoPoint &operator-=(const GeoPoint &rhs)
        {
            _lat -= rhs._lat;
            _lon -= rhs._lon;
            return *this;
        }

        GeoPoint operator*(double v) const
        {
            GeoPoint result(*this);
            result *= v;
            return result;
        }

        GeoPoint &operator*=(double v)
        {
            _lat *= v;
            _lon *= v;
            return *this;
        }

        GeoPoint operator/(double v) const
        {
            GeoPoint result(*this);
            result /= v;
            return result;
        }

        GeoPoint &operator/=(double v)
        {
            _lat /= v;
            _lon /= v;
            return *this;
        }

        GeoPoint &operator=(const GeoPoint &rhs) = default;
        GeoPoint &operator=(GeoPoint &&rhs) = default;
        bool operator==(const GeoPoint &rhs) const = default;
        bool operator!=(const GeoPoint &rhs) const = default;

        FixedPointCoordinate lat() const
        {
            return _lat;
        }

        FixedPointCoordinate lon() const
        {
            return _lon;
        }

        std::string to_string() const {
            std::string result("(");
            result += std::to_string(_lat);
            result += ", ";
            result += std::to_string(_lon);
            result += ")";
            return result;
        }

        std::string to_float_string() const {
            std::string result("(");
            result += std::to_string(_lat / 1e6);
            result += ", ";
            result += std::to_string(_lon / 1e6);
            result += ")";
            return result;
        }

    private:
        FixedPointCoordinate _lat;
        FixedPointCoordinate _lon;
    };
}