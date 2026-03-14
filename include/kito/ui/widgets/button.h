#pragma once
#include <kito/graphics/renderer/renderer.h>
#include <iostream>
#include <kito/ui/widgets/widget.h>

namespace kito::ui {

    class Button: public Widget {

        enum class ButtonState { Normal, Hover, Pressed };
        
        public:
            float x, y, w, h;
            bool wasPressed = false;
            ButtonState state = ButtonState::Normal;

            Button(std::string name, float x, float y, float w, float h) : Widget(name, {x, y, w, h}), x(x), y(y), w(w), h(h) {}

            void update(bool mouseDown, float mouseX, float mouseY);

            void draw(kito::Graphics::Renderer& renderer) override;
            void handleEvent(const KitoEvent& event) override;
    };

}