#include <kito/services/configManager.h>

namespace kito::services {

    ConfigManager::ConfigManager() {
        m_parser = std::make_unique<kito::parser::ConfigParser>();
    }

    ConfigManager::~ConfigManager() = default;

    void ConfigManager::LoadConfig(const std::string& configFile) {
        auto config = m_parser->loadYamlConfig(configFile);

        ConfigManager::setWindowConfig({
            config["title"].as<std::string>("kito app"),
            config["width"].as<int>(800),
            config["height"].as<int>(600),
            config["fullscreen"].as<bool>(false),
            config["resizable"].as<bool>(true)    
        });
    }

}