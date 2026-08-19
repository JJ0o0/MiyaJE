#pragma once

#include <miya/input/key.hpp>
#include <miya/input/mouse_button.hpp>

#include <miya/math/vectors/vec2.hpp>

#include <cstddef>
#include <array>

namespace miya {
    class Input {
        public:
            void BeginFrame();

            bool IsKeyPressed(Key key) const;
            bool IsKeyHeld(Key key) const;
            bool IsKeyReleased(Key key) const;

            bool IsMouseButtonPressed(MouseButton button) const;
            bool IsMouseButtonHeld(MouseButton button) const;
            bool IsMouseButtonReleased(MouseButton button) const;

            math::Vec2 GetMousePosition() const;
            math::Vec2 GetMouseDelta() const;
            math::Vec2 GetScrollDelta() const;

            void SetKeyState(Key key, bool pressed);
            void SetMouseButtonState(MouseButton button, bool pressed);

            void SetMousePosition(const math::Vec2& position);
            void AddScrollDelta(const math::Vec2& delta);

            void Reset();
        private:
            static constexpr size_t KeyCount = static_cast<size_t>(Key::Count);
            static constexpr size_t MouseButtonCount = static_cast<size_t>(MouseButton::Count);

            static size_t GetKeyIndex(Key key);
            static size_t GetMouseButtonIndex(MouseButton button);

            std::array<bool, KeyCount> m_currentKeys{};
            std::array<bool, KeyCount> m_previousKeys{};

            std::array<bool, MouseButtonCount> m_currentMouseButtons{};
            std::array<bool, MouseButtonCount> m_previousMouseButtons{};

            bool m_hasMousePosition = false;
            math::Vec2 m_mousePosition{};
            math::Vec2 m_mouseDelta{};
            math::Vec2 m_scrollDelta{};
    };
}