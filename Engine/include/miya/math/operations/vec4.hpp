#pragma once

#include <miya/math/operations/scalar.hpp>
#include <miya/math/vectors/vec4.hpp>
#include <cmath>

namespace miya::math {
    inline float LengthSquared(const Vec4& vec) {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w);
    }

    inline float Length(const Vec4& vec) {
        return sqrt(LengthSquared(vec));
    }

    inline Vec4 Normalize(const Vec4& vec) {
        const float lengthSquared = LengthSquared(vec);
        if (lengthSquared == 0) return Vec4{0.0f};

        float inverseLength = 1.0f / sqrt(lengthSquared);
        return vec * inverseLength;
    }

    inline float Dot(const Vec4& a, const Vec4& b) {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }

    inline float DistanceSquared(const Vec4& a, const Vec4& b) {
        return LengthSquared(b - a);
    }

    inline float Distance(const Vec4& a, const Vec4& b) {
        return Length(b - a);
    }

    inline Vec4 Lerp(const Vec4& a, const Vec4& b, float t) {
        return (1.0f - t) * a + (t * b);
    }
}