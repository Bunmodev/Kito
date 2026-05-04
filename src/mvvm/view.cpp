#include <kito/mvvm/view.h>

namespace kito::mvvm {

    View::View(const std::string& name) {
        m_name = name;
        // m_viewModel = nullptr;
    }

    void View::setWidgets(std::vector<std::unique_ptr<kito::ui::Widget>> widgets) {
        m_widgets = std::move(widgets);
    }

    const std::vector<std::unique_ptr<kito::ui::Widget>>& View::getWidgets() const {
        return m_widgets;
    }

    // The View handles its own events by passing them down
    void View::handleEvent(const KitoEvent& event) {
        if (event.type == KitoEvent::Type::MouseButtonDown) {
            for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); ++it) {
                // This will drill through the Container to find "btn_7"
                kito::ui::Widget* target = (*it)->findTarget(event.mouse.x, event.mouse.y);
                
                if (target) {
                    // Internal Widget logic (visual states, etc.)
                    target->onClick(); 

                    // ViewModel link (Calculator logic)
                    if (m_viewModel) {
                        m_viewModel->onClick(target->getId());
                    }
                    break; // Stop after the first hit to prevent "click-through"
                }
            }
        }
    }

    void View::render(Graphics::Renderer& renderer) {
        for (auto& widget : m_widgets) {
            widget->draw(renderer);
        }
    }

    void View::bindYamlModel(const YAML::Node& yamlModel) {
        auto newModel = std::make_unique<Model>();

        if (yamlModel.IsMap()) {
            for (auto it = yamlModel.begin(); it != yamlModel.end(); ++it) {
                std::string key = it->first.as<std::string>();
                const YAML::Node& value = it->second;

                // Only process scalar values (ignore nested maps for now)
                if (value.IsScalar()) {
                    newModel->setProperty(key, value);
                }
            }   
        }

        m_models.push_back(std::move(newModel));
        std::cout << "[view]: binding yaml model" << std::endl;
    }

    void View::bindViewModel(ViewModel* vm) {
        m_viewModel = vm;
        if (m_viewModel) {
            std::cout << "[Kito View]: Bound to dynamic logic." << std::endl;
        }
    }

}