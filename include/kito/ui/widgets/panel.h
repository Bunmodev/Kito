#pragma once
#include <kito/graphics/renderer/renderer.h>
#include <iostream>
#include <kito/ui/widgets/widget.h>

namespace kito::ui {

    class Panel: public Widget {
    
        public:
            float x, y, w, h;

            Panel(std::string name, float x, float y, float w, float h) : Widget(name, {x, y, w, h}), x(x), y(y), w(w), h(h) {}

            void update(bool mouseDown, float mouseX, float mouseY);

            void draw(kito::Graphics::Renderer& renderer) override;
            void handleEvent(const KitoEvent& event) override;
    };

}