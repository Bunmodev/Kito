#pragma once
#include <kito/utils/parser/configParser.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>

namespace kito::services {
    
    class VFS {

        protected:
            std::filesystem::path m_basePath;
            std::filesystem::path m_resourcePath;
            std::map<std::string, std::filesystem::path> m_mountPoints;
            bool m_isBundled;
            std::filesystem::path m_modelPath;
            std::filesystem::path m_viewPath;
            std::filesystem::path m_viewModelPath;

            std::map<std::string, std::filesystem::path> m_viewRegistry;
            std::map<std::string, std::filesystem::path> m_modelRegistry;
            std::map<std::string, std::filesystem::path> m_viewModelRegistry;

        public:

            VFS();
           ~VFS();

            void crawlViews();
            void crawlModels();
            void crawlViewModels();

            YAML::Node getView(const std::string& viewName);
            std::filesystem::path getViewPath() { return m_viewPath; };
            void setViewPath(const std::string& viewPath);

            YAML::Node getStyles(const std::string& viewName);

            YAML::Node getModel(const std::string& viewName);
            
            private:
            
            void discoverModels(const std::filesystem::path& folder);
            void discoverViews(const std::filesystem::path& folder);
            void discoverViewModels(const std::filesystem::path& folder);
            void mount(const std::string& resourceName, const std::filesystem::path& resourcePath);
            YAML::Node resolve(const std::string& resourceName, const std::string& resourceType);
    };
}