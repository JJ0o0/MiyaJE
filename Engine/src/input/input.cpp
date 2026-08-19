#include <miya/input/input.hpp>

#include <miya/core/debug/assert.hpp>

namespace miya {
    size_t Input::GetKeyIndex(Key key) {
        size_t index = static_cast<size_t>(key);
        MIYA_ASSERT(index < KeyCount, "Key index out of bounds");
        return index;
    }

    size_t Input::GetMouseButtonIndex(MouseButton button) {
        size_t index = static_cast<size_t>(button);
        MIYA_ASSERT(index < MouseButtonCount, "Mouse Button index out of bounds");
        return index;
    }

    void Input::BeginFrame() {
        m_previousKeys = m_currentKeys;
        m_previousMouseButtons = m_currentMouseButtons;

        m_mouseDelta = math::Vec2(0.0f);
        m_scrollDelta = math::Vec2(0.0f);
    }

    bool Input::IsKeyPressed(Key key) const {
        size_t index = GetKeyIndex(key);
        return m_currentKeys[index] && !m_previousKeys[index];
    }

    bool Input::IsKeyHeld(Key key) const {
        size_t index = GetKeyIndex(key);
        return m_currentKeys[index] && m_previousKeys[index];
    }

    bool Input::IsKeyReleased(Key key) const {
        size_t index = GetKeyIndex(key);
        return !m_currentKeys[index] && m_previousKeys[index];
    }

    bool Input::IsMouseButtonPressed(MouseButton button) const {
        size_t index = GetMouseButtonIndex(button);
        return m_currentMouseButtons[index] && !m_previousMouseButtons[index];
    }

    bool Input::IsMouseButtonHeld(MouseButton button) const {
        size_t index = GetMouseButtonIndex(button);
        return m_currentMouseButtons[index] && m_previousMouseButtons[index];
    }

    bool Input::IsMouseButtonReleased(MouseButton button) const {
        size_t index = GetMouseButtonIndex(button);
        return !m_currentMouseButtons[index] && m_previousMouseButtons[index];
    }

    math::Vec2 Input::GetMousePosition() const { return m_mousePosition; }
    math::Vec2 Input::GetMouseDelta() const { return m_mouseDelta; }
    math::Vec2 Input::GetScrollDelta() const { return m_scrollDelta; }

    void Input::SetKeyState(Key key, bool pressed) {
        size_t index = GetKeyIndex(key);
        m_currentKeys[index] = pressed;
    }

    void Input::SetMouseButtonState(MouseButton button, bool pressed) {
        size_t index = GetMouseButtonIndex(button);
        m_currentMouseButtons[index] = pressed;
    }

    void Input::SetMousePosition(const math::Vec2& position) {
        if (!m_hasMousePosition) {
            m_mousePosition = position;
            m_hasMousePosition = true;
            return;
        }

        m_mouseDelta += position - m_mousePosition;
        m_mousePosition = position;
    }

    void Input::AddScrollDelta(const math::Vec2& delta) {
        m_scrollDelta += delta;
    }
    
    void Input::Reset() {
        m_currentKeys = {};
        m_previousKeys = {};

        m_currentMouseButtons = {};
        m_previousMouseButtons = {};

        m_mouseDelta = math::Vec2(0.0f);
        m_scrollDelta = math::Vec2(0.0f);

        m_hasMousePosition = false;
    }
}