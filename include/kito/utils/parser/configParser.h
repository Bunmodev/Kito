#pragma once

#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>
#include <vector>
#include <kito/ui/core/ui.h>
#include <kito/ui/widgets/widget.h>

namespace kito::parser {
    
    class ConfigParser {

        public:
            static YAML::Node loadYamlConfig(const std::string& filename);
            const std::string getWidgetType(const YAML::Node& widgetNode);
            std::vector<std::unique_ptr<kito::ui::Widget>> getWidgets(const YAML::Node& config);
    };
}