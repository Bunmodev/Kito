#pragma once
#include <kito/ui/core/inflate.h>
#include <memory>
#include <iostream>
#include <kito/core/window.h>
#include <kito/graphics/renderer/renderer.h>
#include <kito/core/events.h>
#include <kito/mvvm/view.h>
#include <kito/mvvm/model.h>
#include <kito/mvvm/viewModel.h>
#include <kito/services/vfs.h>
#include <kito/services/viewModelManager.h>

namespace kito::ui {
    class Inflate;
};

namespace kito {
    class Window;
}

namespace kito::Graphics {
    class Renderer;
}

namespace kito::mvvm {
    class View;
    class Model;
    class ViewModel;
}

namespace kito::services {

    struct ViewEntry {
        std::string yamlPath;
        std::unique_ptr<mvvm::View> instance;
    };

    class ViewManager {

        protected:

        public:
            ViewManager();
            ~ViewManager() = default;

            void renderView(Graphics::Renderer& renderer, Window& window);
            void handleEvent(const KitoEvent& event);

            void loadView(const std::string& name, const YAML::Node& node, Window& window);
            mvvm::View* getView(const std::string& name, Window& window);

            std::unique_ptr<mvvm::View> getCurrentView();

        private:
            std::unique_ptr<ui::Inflate> m_inflate;
            std::unique_ptr<mvvm::View> m_activeView;
            std::unordered_map<std::string, ViewEntry> m_registry;
            std::unique_ptr<VFS> m_vfs;
            std::unique_ptr<ViewModelManager> m_vmManager;

    };
}