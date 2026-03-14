#pragma once
#include <SDL3/SDL.h>
#include <kito/core/events.h>

namespace kito::utils {

    class SDLScanner {
    public:
        static KitoEvent MapToKito(const SDL_Event& sdlEvent) {
            KitoEvent kEvent{}; // Initialize to zero

            switch (sdlEvent.type) {
                case SDL_EVENT_QUIT:
                    kEvent.type = KitoEvent::Type::Quit;
                    break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    kEvent.type = (sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
                                  ? KitoEvent::Type::MouseButtonDown 
                                  : KitoEvent::Type::MouseButtonUp;
                    kEvent.mouse.x = static_cast<int>(sdlEvent.button.x);
                    kEvent.mouse.y = static_cast<int>(sdlEvent.button.y);
                    kEvent.mouse.button = sdlEvent.button.button; // 1=L, 2=M, 3=R
                    break;

                case SDL_EVENT_MOUSE_MOTION:
                    kEvent.type = KitoEvent::Type::MouseMove;
                    kEvent.mouse.x = static_cast<int>(sdlEvent.motion.x);
                    kEvent.mouse.y = static_cast<int>(sdlEvent.motion.y);
                    break;

                case SDL_EVENT_KEY_DOWN:
                case SDL_EVENT_KEY_UP:
                    kEvent.type = (sdlEvent.type == SDL_EVENT_KEY_DOWN) 
                                  ? KitoEvent::Type::KeyDown 
                                  : KitoEvent::Type::KeyUp;
                    kEvent.keyboard.keycode = sdlEvent.key.key;
                    kEvent.keyboard.repeat = sdlEvent.key.repeat;
                    break;

                case SDL_EVENT_WINDOW_RESIZED:
                    kEvent.type = KitoEvent::Type::WindowResize;
                    kEvent.window.width = sdlEvent.window.data1;
                    kEvent.window.height = sdlEvent.window.data2;
                    break;

                default:
                    // You can add a 'None' or 'Unknown' type to your enum 
                    // to ignore events you don't care about yet.
                    kEvent.type = KitoEvent::Type::None;
                    break;
            }

            return kEvent;
        }
    };
}