#pragma once

#include <miya/math/constants.hpp>

#include <miya/core/debug/assert.hpp>

#include <cmath>

namespace miya::math {
    constexpr float ToRadians(float degrees) { return (degrees * constants::PI) / 180.0f; }
    constexpr float ToDegrees(float radians) { return (radians * 180.0f) / constants::PI; }

    inline float Floor(float value) { return std::floor(value); }

    inline float Log2(float value) {
        MIYA_ASSERT(value > 0.0f, "Value cannot be less or equal to zero");
        return std::log2(value);
    }

    template<typename T>
    constexpr T Max(T a, T b) {
        return a > b ? a : b;
    }

    template<typename T>
    constexpr T Min(T a, T b) {
        return a < b ? a : b;
    }

    inline float Sin(float radians) { return std::sin(radians); }
    inline float Cos(float radians) { return std::cos(radians); }
    inline float Tan(float radians) { return std::tan(radians); }

    inline float Asin(float value) { return std::asin(value); }
    inline float Acos(float value) { return std::acos(value); }
    inline float Atan(float value) { return std::atan(value); }
    inline float Atan2(float y, float x) { return std::atan2(y, x); }

    inline float Exp(float value) { return std::exp(value); }

    inline float Clamp(float value, float min, float max) {
        MIYA_ASSERT(min <= max, "Minimum cannot be greater than Maximum value");

        if (value < min) return min;
        if (value > max) return max;

        return value;
    }

    inline float Lerp(float from, float to, float weight) { return from + (to - from) * weight; }
    inline float ExponentialSmoothing(float value, float time) { return 1.0f - Exp(-value * time); }
}
