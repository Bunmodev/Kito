#pragma once
#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>
#include <vector>
#include <kito/ui/widgets/widget.h>
#include <kito/ui/widgets/button.h>
#include <kito/ui/widgets/panel.h>
#include <kito/ui/widgets/container.h>
#include <kito/utils/parser/configParser.h>

namespace kito::ui {
    class Widget;
    class Button;
    class Panel;
    class Container;
}

namespace kito::ui_factory {
    // This is the "Brain" that knows all widget types
    std::unique_ptr<kito::ui::Widget> createWidget(const YAML::Node& node, Window& window);
    std::unique_ptr<kito::ui::Widget> createKMLWidget(const std::string& widgetType, const std::vector<std::pair<std::string, std::string>>& attributes);
}