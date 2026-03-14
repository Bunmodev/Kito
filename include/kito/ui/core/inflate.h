#pragma once
#include <kito/ui/core/ui.h>
#include <vector>

namespace kito::ui {

    class Inflate {
        public:
            Inflate() = default;
            ~Inflate() = default;

            std::vector<std::unique_ptr<ui::Widget>> inflateYaml(const YAML::Node& yamlView, Window& window);
    };
}