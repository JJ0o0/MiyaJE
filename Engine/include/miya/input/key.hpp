#pragma once

namespace miya {
    enum class Key {
        Unknown,

        Q, W, E, R, T, Y, U, I, O, P,
        A, S, D, F, G, H, J, K, L,
        Z, X, C, V, B, N, M,

        One, Two, Three, Four, Five,
        Six, Seven, Eight, Nine, Zero,

        F1, F2, F3, F4, F5, F6,
        F7, F8, F9, F10, F11, F12,

        Space,
        Enter,
        Escape,
        Tab,
        Backspace,
        Delete,
        Insert,

        LeftShift, RightShift,
        LeftControl, RightControl,
        LeftAlt, RightAlt,
        LeftSuper, RightSuper,

        Up, Down, Left, Right,

        Home, End,
        PageUp, PageDown,

        CapsLock,
        NumLock,
        ScrollLock,

        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,
        Semicolon,
        Equal,
        LeftBracket,
        Backslash,
        RightBracket,
        GraveAccent,

        World1,
        World2,

        Count
    };
}