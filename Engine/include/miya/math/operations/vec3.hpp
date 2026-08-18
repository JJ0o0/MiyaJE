#pragma once

#include <miya/math/operations/scalar.hpp>
#include <miya/math/vectors/vec3.hpp>
#include <cmath>

namespace miya::math {
    inline float LengthSquared(const Vec3& vec) {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    }

    inline float Length(const Vec3& vec) {
        return sqrt(LengthSquared(vec));
    }

    inline Vec3 Normalize(const Vec3& vec) {
        const float lengthSquared = LengthSquared(vec);
        if (lengthSquared == 0) return Vec3{0.0f};

        float inverseLength = 1.0f / sqrt(lengthSquared);
        return vec * inverseLength;
    }

    inline float Dot(const Vec3& a, const Vec3& b) {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    inline float DistanceSquared(const Vec3& a, const Vec3& b) {
        return LengthSquared(b - a);
    }

    inline float Distance(const Vec3& a, const Vec3& b) {
        return Length(b - a);
    }

    inline Vec3 Lerp(const Vec3& a, const Vec3& b, float t) {
        return (1.0f - t) * a + (t * b);
    }

    inline Vec3 Cross(const Vec3& a, const Vec3& b) {
        return Vec3 {
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        };
    }
}