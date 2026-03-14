#pragma once

#include <string>
#include <unordered_map>
#include <any>
#include <stdexcept>
#include <kito/core/types.h>
#include <kito/utils/parser/configParser.h>

namespace kito::parser {
    class ConfigParser;
}

namespace kito::services {
    class ConfigManager {

        

        protected:
            WindowConfig m_windowConfig;


        public:
            ConfigManager();
            ~ConfigManager();

            void LoadConfig(const std::string& configFile);

            WindowConfig getWindowConfig() const {return m_windowConfig;};
            void setWindowConfig(const WindowConfig& config) {m_windowConfig = config;};

        private:

            std::unique_ptr<kito::parser::ConfigParser> m_parser;
    };
}