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
        for (auto& widget : m_widgets) {
            widget->handleEvent(event);
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

    void bindViewModel(const std::unique_ptr<ViewModel>& vm) {
        // m_viewModel = std::move(vm);
        std::cout << "binding vm" << std::endl;
    }

}