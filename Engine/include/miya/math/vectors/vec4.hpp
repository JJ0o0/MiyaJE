#pragma once

#include "vec2.hpp"
#include "vec3.hpp"

namespace miya::math {
    struct Vec4 {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        constexpr Vec4() = default;
        constexpr Vec4(float xValue, float yValue, float zValue, float wValue) : x(xValue), y(yValue), z(zValue), w(wValue) {}
        constexpr Vec4(const Vec2& xy, float zValue, float wValue) : x(xy.x), y(xy.y), z(zValue), w(wValue) {}
        constexpr Vec4(const Vec3& xyz, float wValue) : x(xyz.x), y(xyz.y), z(xyz.z), w(wValue) {}
        
        explicit constexpr Vec4(float value) : x(value), y(value), z(value), w(value) {}
        
        constexpr Vec3 XYZ() const { return {x, y, z}; }

        Vec4& operator+=(const Vec4& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }

        Vec4& operator-=(const Vec4& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }

        Vec4& operator*=(const Vec4& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }

        Vec4& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }
    };

    inline Vec4 operator+(Vec4 left, const Vec4& right) {
        left += right;
        return left;
    }

    inline Vec4 operator-(Vec4 left, const Vec4& right) {
        left -= right;
        return left;
    }

    inline Vec4 operator*(Vec4 left, const Vec4& right) {
        left *= right;
        return left;
    }

    inline Vec4 operator*(Vec4 vector, float scalar) {
        vector.x *= scalar;
        vector.y *= scalar;
        vector.z *= scalar;
        vector.w *= scalar;
        return vector;
    }

    inline Vec4 operator*(float scalar, Vec4 vector) {
        vector.x *= scalar;
        vector.y *= scalar;
        vector.z *= scalar;
        vector.w *= scalar;
        return vector;
    }

    inline Vec4 operator-(const Vec4& vector) {
        return {-vector.x, -vector.y, -vector.z, -vector.w};
    }

    inline Vec4 ToPoint(const Vec3& value) { return Vec4{value, 1.0f}; }
    inline Vec4 ToDirection(const Vec3& value) { return Vec4{value, 0.0f}; }
}
