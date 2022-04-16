#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

/*
struct Point2D
{
    float values[2] {};

    Point2D() {}
    Point2D(float x, float y) : values { x, y } {}

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    Point2D& operator+=(const Point2D& other)
    {
        x() += other.x();
        y() += other.y();
        return *this;
    }

    Point2D& operator*=(const Point2D& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point2D& operator*=(const float scalar)
    {
        x() *= scalar;
        y() *= scalar;
        return *this;
    }

    Point2D operator+(const Point2D& other) const
    {
        Point2D result = *this;
        result += other;
        return result;
    }

    Point2D operator*(const Point2D& other) const
    {
        Point2D result = *this;
        result *= other;
        return result;
    }

    Point2D operator*(const float scalar) const
    {
        Point2D result = *this;
        result *= scalar;
        return result;
    }
};
*/

template<typename type, int dimensions, typename = std::enable_if_t<std::is_arithmetic_v<type>>>
struct Point
{
    std::array<type, dimensions> values;

    template <typename ...T> explicit Point(T&& ... values_)
            : values {static_cast<type>(values_) ...} {
        static_assert(dimensions>0);
        static_assert(sizeof...(values_) == dimensions);
    }
    type& x() { return values[0]; }
    type x() const { return values[0]; }

    type& y() { static_assert(dimensions>1);return values[1]; }
    type y() const { static_assert(dimensions>1);return values[1]; }

    type& z() { static_assert(dimensions>2);return values[2]; }
    type z() const { static_assert(dimensions>2);return values[2]; }

    Point<type, dimensions>& operator+=(const Point<type, dimensions>& other) {
        std::transform(values.cbegin(), values.cend(), other.values.cbegin(), values.begin(), std::plus<>());
        return *this;
    }

    Point<type, dimensions>& operator-=(const Point<type, dimensions>& other) {
        std::transform(values.cbegin(), values.cend(), other.values.cbegin(), values.begin(), std::minus<>());
        return *this;
    }

    Point<type, dimensions>& operator*=(const Point<type, dimensions>& other) {
        std::transform(values.cbegin(), values.cend(), other.values.cbegin(), values.begin(), std::multiplies<>());
        return *this;
    }

    Point<type, dimensions>& operator*=(const float scalar)
    {
        std::transform(values.cbegin(), values.cend(), values.begin(), [scalar](float x){return x*scalar;});
        return *this;
    }

    Point<type, dimensions> operator+(const Point<type, dimensions>& other) const
    {
        Point<type, dimensions> result = *this;
        result += other;
        return result;
    }

    Point<type, dimensions> operator-(const Point<type, dimensions>& other) const
    {
        Point<type, dimensions> result = *this;
        result -= other;
        return result;
    }

    Point<type, dimensions> operator*(const Point<type, dimensions>& other) const
    {
        Point<type, dimensions> result = *this;
        result *= other;
        return result;
    }

    Point<type, dimensions> operator*(const float scalar) const
    {
        Point<type, dimensions> result = *this;
        result *= scalar;
        return result;
    }

    Point<type, dimensions> operator-() const
    {
        return *this * -1;
    }

    float length() const {
        auto o = std::transform_reduce(
            values.begin(),
            values.end(),
            0.f,
            [](float x, float y){return x+y;},
            [](const float x){return x*x;}
        );
        return std::sqrt(o);
    }

    float distance_to(const Point<type, dimensions>& other) const { return (*this - other).length(); }

    Point<type, dimensions>& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }


    Point<type, dimensions>& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};

using Point3D = Point<float, 3>;
using Point2D = Point<float, 2>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return Point2D{ .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}


/*
inline Point<float, 2> project_2D(const Point<float, 3>& p)
{
    Point<float, 2> point;
    point.x() = .5f * p.x() - .5f * p.y();
    point.y() = .5f * p.x() + .5f * p.y() + p.z();
    return point;
}
 */