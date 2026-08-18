#pragma once

#include <miya/math/vectors/vec4.hpp>

#include <miya/core/debug/assert.hpp>

#include <cstddef>

namespace miya::math {
    struct Mat4 {
        float Data[16]{};

        constexpr Mat4() = default;

        explicit constexpr Mat4(float diagonal) : Data{} {
            Data[0] = diagonal;
            Data[5] = diagonal;
            Data[10] = diagonal;
            Data[15] = diagonal;
        }

        float& operator()(size_t row, size_t column) {
            MIYA_ASSERT(row < 4, "Matrix row out of bounds");
            MIYA_ASSERT(column < 4, "Matrix column out of bounds");

            return Data[(column * 4) + row];
        }

        const float& operator()(size_t row, size_t column) const {
            MIYA_ASSERT(row < 4, "Matrix row out of bounds");
            MIYA_ASSERT(column < 4, "Matrix column out of bounds");

            return Data[(column * 4) + row];
        }

        Mat4& operator*=(const Mat4& other) {
            Mat4 result{};

            for (size_t row = 0; row < 4; row++) {
                for (size_t column = 0; column < 4; column++) {
                    for (size_t k = 0; k < 4; k++) {
                        result(row, column) += (*this)(row, k) * other(k, column);
                    }
                }
            }

            *this = result;
            return *this;
        }
    };

    inline Mat4 operator*(Mat4 left, const Mat4& right) {
        left *= right;
        return left;
    }

    inline Vec4 operator*(const Mat4& matrix, const Vec4& vector) {
        return {
            matrix(0, 0) * vector.x +
            matrix(0, 1) * vector.y +
            matrix(0, 2) * vector.z +
            matrix(0, 3) * vector.w,

            matrix(1, 0) * vector.x +
            matrix(1, 1) * vector.y +
            matrix(1, 2) * vector.z +
            matrix(1, 3) * vector.w,

            matrix(2, 0) * vector.x +
            matrix(2, 1) * vector.y +
            matrix(2, 2) * vector.z +
            matrix(2, 3) * vector.w,

            matrix(3, 0) * vector.x +
            matrix(3, 1) * vector.y +
            matrix(3, 2) * vector.z +
            matrix(3, 3) * vector.w
        };
    }
}
