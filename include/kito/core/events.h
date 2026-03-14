#pragma once
#include <cstdint> // For uint8_t

namespace kito {

    struct KitoEvent {
        enum class Type {
            Quit,           // The "Emergency Brake"
            MouseButtonDown,
            MouseButtonUp,
            MouseMove,
            KeyDown,
            KeyUp,
            WindowResize,
            None            // A "None" type to represent uninitialized or ignored events
        };

        Type type;

        // The union stays the same, 
        // but 'Quit' won't need to access any of these members.
        union {
            struct {
                int x, y;
                uint8_t button;
            } mouse;
            struct {
                int keycode;
                bool repeat;
            } keyboard;
            struct {
                int width, height;
            } window;
        };
    };
}