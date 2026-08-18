#pragma once

#include <miya/math/operations/scalar.hpp>
#include <miya/math/vectors/vec2.hpp>
#include <cmath>

namespace miya::math {
    inline float LengthSquared(const Vec2& vec) {
        return (vec.x * vec.x) + (vec.y * vec.y);
    }

    inline float Length(const Vec2& vec) {
        return sqrt(LengthSquared(vec));
    }

    inline Vec2 Normalize(const Vec2& vec) {
        const float lengthSquared = LengthSquared(vec);
        if (lengthSquared == 0) return Vec2{0.0f};

        float inverseLength = 1.0f / sqrt(lengthSquared);
        return vec * inverseLength;
    }

    inline float Dot(const Vec2& a, const Vec2& b) {
        return (a.x * b.x) + (a.y * b.y);
    }

    inline float DistanceSquared(const Vec2& a, const Vec2& b) {
        return LengthSquared(b - a);
    }

    inline float Distance(const Vec2& a, const Vec2& b) {
        return Length(b - a);
    }

    inline Vec2 Lerp(const Vec2& a, const Vec2& b, float t) {
        return (1.0f - t) * a + (t * b);
    }

    inline float Cross(const Vec2& a, const Vec2& b) {
        return (a.x * b.y) - (a.y * b.x);
    }

    inline Vec2 PerpendicularCCW(const Vec2& vec) {
        return Vec2 {-vec.y, vec.x};
    }

    inline Vec2 PerpendicularCW(const Vec2& vec) {
        return Vec2 {vec.y, -vec.x};
    }

    inline Vec2 Rotate(const Vec2& vec, float theta) {
        float thetaSin = Sin(theta);
        float thetaCos = Cos(theta);

        return Vec2 {
            (vec.x * thetaCos) - (vec.y * thetaSin),
            (vec.x * thetaSin) + (vec.y * thetaCos)
        };
    }
}