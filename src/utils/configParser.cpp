#include <kito/utils/parser/configParser.h>

namespace kito::parser {

    YAML::Node ConfigParser::loadYamlConfig(const std::string& filename) {
        try {
            YAML::Node config = YAML::LoadFile(filename);
            return config;
        } catch (const std::exception& e) {
            std::cerr << "Error loading config: " << e.what() << std::endl;
            return YAML::Node(); // Return empty node on failure
        }
    }

    const std::string ConfigParser::getWidgetType(const YAML::Node& widgetNode) {
        if (widgetNode["type"]) {
            return widgetNode["type"].as<std::string>();
        }
        return "unknown";
    }

    // a helper function to return all widgets as objects from the config
    // std::vector<std::unique_ptr<kito::ui::Widget>> ConfigParser::getWidgets(const YAML::Node& config) {
    //     std::vector<std::unique_ptr<kito::ui::Widget>> widgets;
    //     if (config["window"] && config["window"]["widgets"]) {
    //         for (const auto& widgetNode : config["window"]["widgets"]) {
    //             auto widget = kito::ui_factory::createWidget(widgetNode, config);
    //             widgets.push_back(std::move(widget));
    //         }
    //     }
    //     return widgets;
    // }
}