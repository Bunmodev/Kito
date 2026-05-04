#include <kito/services/viewManager.h>

namespace kito::services {

    ViewManager::ViewManager() {
        m_inflate = std::make_unique<ui::Inflate>();
        m_vfs = std::make_unique<VFS>();
        m_vmManager = std::make_unique<ViewModelManager>(*m_vfs);
    }

    void ViewManager::loadView(const std::string& name, const YAML::Node& node, Window& window) {
        auto newView = std::make_unique<mvvm::View>(name);

        // 1. Handle Models
        if (node["link"]["model"]) {
            std::vector<std::string> models = node["link"]["model"].as<std::vector<std::string>>();
            for(const std::string& modelName : models) {
                auto yamlModel = m_vfs->getModel(modelName);
                newView->bindYamlModel(yamlModel);
            }
        }

        // 2. Handle ViewModel (The .dat hex-link)
        if (node["link"]["viewModel"]) {
            std::string vmKey = node["link"]["viewModel"].as<std::string>();
            
            // CRITICAL: Load it first! This triggers the VFS path lookup and LoadLibrary
            m_vmManager->loadViewModel(vmKey);
            
            // Now get the living instance from the registry
            mvvm::ViewModel* vm = m_vmManager->getViewModel(vmKey);
            
            if (vm) {
                newView->bindViewModel(vm);
            } else {
                std::cerr << "[Kito UI]: Failed to bind ViewModel: " << vmKey << std::endl;
            }
        }

        // 3. Inflate and Set
        auto widgets = m_inflate->inflateYaml(node, window);
        
        // Pro Tip: If your widgets need to talk to the VM immediately, 
        // you should pass the 'vm' pointer into the inflator here.
        newView->setWidgets(std::move(widgets));

        m_activeView = std::move(newView);
        
        // std::cout << "[Kito UI]: View '" << name << "' loaded with " 
        //         << (m_activeView->hasViewModel() ? "active" : "no") << " logic." << std::endl;
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