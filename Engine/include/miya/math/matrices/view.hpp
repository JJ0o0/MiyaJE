#pragma once

#include <miya/math/operations/vec3.hpp>
#include <miya/math/matrices/mat4.hpp>
#include <miya/math/vectors/vec3.hpp>

#include <miya/core/debug/assert.hpp>

namespace miya::math {
    inline Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
        MIYA_ASSERT(LengthSquared(target - eye) > 0.0f, "Eye and Target cannot have the same position");
        MIYA_ASSERT(LengthSquared(up) > 0.0f, "Up has length zero");

        Vec3 forward = Normalize(target - eye);
        MIYA_ASSERT(LengthSquared(Cross(forward, up)) > 0.0f, "Forward and Up vectors are collinear");

        Vec3 right = Normalize(Cross(forward, up));
        Vec3 cameraUp = Cross(right, forward);

        Mat4 result{1.0f};

        result(0, 0) = right.x;
        result(0, 1) = right.y;
        result(0, 2) = right.z;
        result(0, 3) = -Dot(right, eye);

        result(1, 0) = cameraUp.x;
        result(1, 1) = cameraUp.y;
        result(1, 2) = cameraUp.z;
        result(1, 3) = -Dot(cameraUp, eye);

        result(2, 0) = -forward.x;
        result(2, 1) = -forward.y;
        result(2, 2) = -forward.z;
        result(2, 3) = Dot(forward, eye);

        result(3, 3) = 1.0f;

        return result;
    }
}
