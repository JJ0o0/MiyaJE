#pragma once

#include <miya/math/operations/scalar.hpp>
#include <miya/math/matrices/mat4.hpp>
#include <miya/math/vectors/vec4.hpp>
#include <miya/math/vectors/vec3.hpp>
#include <miya/math/constants.hpp>

#include <miya/core/debug/assert.hpp>

namespace miya::math {
    inline Mat4 PerspectiveZeroToOne(
        float fovyRadians, 
        float aspectRatio, 
        float nearPlane, float farPlane
    ) {
        MIYA_ASSERT(fovyRadians > 0.0f, "Field Of View must be greater than zero");
        MIYA_ASSERT(fovyRadians < constants::PI, "Field of view must be less than PI");
        MIYA_ASSERT(aspectRatio > 0.0f, "Aspect Ratio must be greater than zero");
        MIYA_ASSERT(nearPlane > 0.0f, "Near Plane must be greater than zero");
        MIYA_ASSERT(farPlane > nearPlane, "Far Plane must be greater than Near Plane");

        const float scale = 1.0f / Tan(fovyRadians * 0.5f);

        Mat4 result{};
        result(0, 0) = scale / aspectRatio;
        result(1, 1) = scale;
        result(2, 2) = farPlane / (nearPlane - farPlane);
        result(2, 3) = (farPlane * nearPlane) / (nearPlane - farPlane);
        result(3, 2) = -1.0f;

        return result;
    }

    inline Mat4 PerspectiveNegativeOneToOne(
        float fovyRadians, 
        float aspectRatio, 
        float nearPlane, float farPlane
    ) {
        MIYA_ASSERT(fovyRadians > 0.0f, "Field Of View must be greater than zero");
        MIYA_ASSERT(fovyRadians < constants::PI, "Field of view must be less than PI");
        MIYA_ASSERT(aspectRatio > 0.0f, "Aspect Ratio must be greater than zero");
        MIYA_ASSERT(nearPlane > 0.0f, "Near Plane must be greater than zero");
        MIYA_ASSERT(farPlane > nearPlane, "Far Plane must be greater than Near Plane");

        const float scale = 1.0f / Tan(fovyRadians * 0.5f);

        Mat4 result{};
        result(0, 0) = scale / aspectRatio;
        result(1, 1) = scale;
        result(2, 2) = -(farPlane + nearPlane) / (farPlane - nearPlane);
        result(2, 3) = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
        result(3, 2) = -1.0f;

        return result;
    }

    inline Vec3 PerspectiveDivide(const Vec4& vec) {
        MIYA_ASSERT(vec.w != 0.0f, "Cannot perform perspective divide with W being Zero");
        return { vec.x / vec.w, vec.y / vec.w, vec.z / vec.w };
    }

    inline auto& Perspective = PerspectiveZeroToOne;
    inline auto& PerspectiveGLClassic = PerspectiveNegativeOneToOne;
}
