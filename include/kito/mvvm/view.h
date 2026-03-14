#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <kito/core/events.h>
#include <kito/ui/widgets/widget.h>
#include <kito/graphics/renderer/renderer.h>
#include <kito/mvvm/model.h>
#include <kito/mvvm/viewModel.h>
#include <yaml-cpp/yaml.h>


namespace kito::ui {
    class Widget;
}



namespace kito::mvvm {
    
    class View {
        public:
            View(const std::string& name);
            ~View() = default;

            void setWidgets(std::vector<std::unique_ptr<kito::ui::Widget>> widgets);
            const std::vector<std::unique_ptr<kito::ui::Widget>>& getWidgets() const;
            void handleEvent(const KitoEvent& event);
            void render(Graphics::Renderer& renderer);
            void bindYamlModel(const YAML::Node& yamlModel);

        private:
            std::string m_name;
            std::vector<std::unique_ptr<kito::ui::Widget>> m_widgets;
            std::vector<std::unique_ptr<Model>> m_models;
    };
}