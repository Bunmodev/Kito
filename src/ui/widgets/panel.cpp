#include <kito/ui/widgets/panel.h>

namespace kito::ui {

    void Panel::update(bool mouseDown, float mouseX, float mouseY) {
        // Panels might have specific logic in the future, but for now they just update their children
        // Widget::update(mouseDown, mouseX, mouseY);
    }

    void Panel::handleEvent(const KitoEvent& event) {
        // Panels might handle events differently in the future, but for now they just pass them to their children
        for (auto& child : children) {
            child->handleEvent(event);
        }
    }

    void Panel::draw(kito::Graphics::Renderer& renderer) {
        // Draw panel background (for demonstration)
        auto rect = getRect();
        renderer.submit({static_cast<float>(rect.x), static_cast<float>(rect.y), static_cast<float>(rect.w), static_cast<float>(rect.h)}, {255, 0, 0, 255}, 2);

        // Draw children on top of the panel background
        // Widget::draw(renderer);
    }
}