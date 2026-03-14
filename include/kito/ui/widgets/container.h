#pragma once
#include <kito/graphics/renderer/renderer.h>
#include <iostream>
#include <kito/ui/widgets/widget.h>

namespace kito::ui {

    class Container: public Widget {
    
        public:
            Container(std::string name, float x, float y, float w, float h) : Widget(name, {x, y, w, h}) {}

            void update(bool mouseDown, float mouseX, float mouseY);

            void draw(kito::Graphics::Renderer& renderer) override;
            void handleEvent(const KitoEvent& event) override;
    };

}