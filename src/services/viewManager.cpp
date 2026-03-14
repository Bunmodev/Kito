#include <kito/services/viewManager.h>

namespace kito::services {

    ViewManager::ViewManager() {
        m_inflate = std::make_unique<ui::Inflate>();
        m_vfs = std::make_unique<VFS>();
    }

    void ViewManager::loadView(const std::string& name, const YAML::Node& node, Window& window) {
        auto newView = std::make_unique<mvvm::View>(name);

        std::vector<std::string> models = node["link"]["model"].as<std::vector<std::string>>();
        for(const std::string model: models) {
            auto yamlModel = m_vfs->getModel(model);
            newView->bindYamlModel(yamlModel);
        }

        std::cout << "current models in view: " << models.size() << std::endl;
        
        // Inflate ONCE
        auto widgets = m_inflate->inflateYaml(node, window);
        newView->setWidgets(std::move(widgets));
        
        m_activeView = std::move(newView);
    }

    mvvm::View* ViewManager::getView(const std::string& name, Window& window) {
        auto& entry = m_registry[name];
        if (!entry.instance) {
            std::cout << "[Kito]: Lazy Loading View: " << name << "\n";
            // Call your Inflater here
            auto entryYaml = m_vfs->getView(name);
            auto widgets = m_inflate->inflateYaml(entryYaml, window);
            entry.instance = std::make_unique<mvvm::View>(name);
            entry.instance->setWidgets(std::move(widgets));
        }
        return entry.instance.get();
    }

    // std::unique_ptr<mvvm::View> ViewManager::getCurrentView() {
    //     return m_activeView;
    // }

    void ViewManager::renderView(Graphics::Renderer& renderer, Window& window) {
        // auto widgetTree = m_inflate->inflateYaml(view, window);
        const auto& widgetTree = m_activeView->getWidgets();
        renderer.draw_widgets(widgetTree, window);
    };

    void ViewManager::handleEvent(const KitoEvent& event) {
        if (m_activeView) {
            m_activeView->handleEvent(event);
        }
    }
}