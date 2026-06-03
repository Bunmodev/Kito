#include <kito/ui/widgets/button.h>

namespace kito::ui {

    void Button::update(bool mouseDown, float mouseX, float mouseY) {
        auto rect = getRect();
        bool inside = mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                        mouseY >= rect.y && mouseY <= rect.y + rect.h;

        if (inside && mouseDown && !wasPressed) {
            std::cout << "Button clicked\n";
            wasPressed = true;
        }

        if (!mouseDown) {
            wasPressed = false;
        }
    }

    void Button::handleEvent(const KitoEvent& event) {
        float mx = event.mouse.x;
        float my = event.mouse.y;
        auto rect = getRect();
        bool inside = (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h);

        if (event.type == KitoEvent::Type::MouseMove) {
            if (inside) {
                // Only set hover if we aren't currently clicking it
                if (state != ButtonState::Pressed) state = ButtonState::Hover;
            } else {
                state = ButtonState::Normal;
            }
        }

        if (event.type == KitoEvent::Type::MouseButtonDown) {
            if (inside) {
                state = ButtonState::Pressed;
                std::cout << "[Kito]: Button Sink!\n";
            }
        }

        if (event.type == KitoEvent::Type::MouseButtonUp) {
            // This is the classic "Win95" logic:
            // Trigger only if we were pressing AND we are still inside
            if (state == ButtonState::Pressed && inside) {
                this->onClick(); 
                std::cout << "[Kito]: Button Pop & Trigger!\n";
            }
            
            // Reset to appropriate state
            state = inside ? ButtonState::Hover : ButtonState::Normal;
        }

    }

    void Button::draw(kito::Graphics::Renderer& renderer) {
        auto rect = getRect();
        auto contentRect = getContentBounds();
        bool pressed = (state == ButtonState::Pressed);
        bool hover   = (state == ButtonState::Hover);

        float offset = pressed ? 6.0f : 0.0f; // exaggerated so we SEE movement

        float x = rect.x + offset;
        float y = rect.y + offset;
        float w = rect.w - offset * 2;
        float h = rect.h - offset * 2;

        float content_x = contentBounds.x;
        float content_y = contentBounds.y;
        float content_w = contentBounds.width;
        float content_h = contentBounds.height;

        SDL_Color faceColor;
        SDL_Color contentColor = {255, 255, 0, 255};

        // LOUD STATE COLORS
        if (pressed) {
            faceColor = {117, 117, 117, 255};     // red
            // std::cout << "[pressed]: going with red" << std::endl;
        } else if (hover) {
            faceColor = {161, 161, 161, 255};     // green
            // std::cout << "[hovered]: going with green" << std::endl;
        } else {
            faceColor = {199, 197, 197, 255};     // blue
            // std::cout << "[normal]: going with blue" << std::endl;
        }

        renderer.submit({x, y, w, h}, faceColor, 1);
        // renderer.submit({content_x, content_y, content_w, content_h}, contentColor, 1);
        
    }

}