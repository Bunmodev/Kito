#include <kito/ui/widgets/container.h>

namespace kito::ui {

    void Container::update(bool mouseDown, float mouseX, float mouseY) {
        // Containers might have specific logic in the future, but for now they just update their children
        // Widget::update(mouseDown, mouseX, mouseY);
    }

    void Container::handleEvent(const KitoEvent& event) {
        // Containers might handle events differently in the future, but for now they just pass them to their children
        for (auto& child : children) {
            child->handleEvent(event);
        }
    }

    void Container::draw(kito::Graphics::Renderer& renderer) {
        // Draw Container background (for demonstration)
        auto rect = getRect();
        renderer.submit({static_cast<float>(rect.x), static_cast<float>(rect.y), static_cast<float>(rect.w), static_cast<float>(rect.h)}, {41, 91, 230, 255}, 2);

        for (auto& child : children) {
            child->draw(renderer);
        }

        // std::cout << "container children number: " << children.size() << std::endl;
    }
}