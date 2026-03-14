#include <kito/services/vfs.h>

namespace kito::services {

    VFS::VFS() {
        m_basePath = std::filesystem::current_path().string();
        m_viewPath = (std::filesystem::path(m_basePath) / "src" / "views").string();
        m_modelPath = (std::filesystem::path(m_basePath) / "src" / "models").string();
        
        // Auto-crawl on startup so the registry is ready
        crawlViews();
        crawlModels();
    }

    VFS::~VFS() = default;

    YAML::Node VFS::getView(const std::string& viewName) {
        // 1. Check if we actually have this screen in our registry
        if (m_viewRegistry.find(viewName) == m_viewRegistry.end()) {
            std::cerr << "[Kito VFS]: Error - View '" << viewName << "' not found in registry!" << std::endl;
            return YAML::Node(); // Return null node
        }

        // 2. Load the file using the path from our registry
        try {
            return YAML::LoadFile(m_viewRegistry[viewName].string());
        } catch (const YAML::Exception& e) {
            std::cerr << "[Kito VFS]: YAML Parsing Error in '" << viewName << "': " << e.what() << std::endl;
            return YAML::Node();
        }
    }

    YAML::Node VFS::getModel(const std::string& modelName) {
        // 1. Check if we actually have this screen in our registry
        if (m_modelRegistry.find(modelName) == m_modelRegistry.end()) {
            std::cerr << "[Kito VFS]: Error - Model '" << modelName << "' not found in registry!" << std::endl;
            return YAML::Node(); // Return null node
        }

        // 2. Load the file using the path from our registry
        try {
            return YAML::LoadFile(m_modelRegistry[modelName].string());
        } catch (const YAML::Exception& e) {
            std::cerr << "[Kito VFS]: YAML Parsing Error in '" << modelName << "': " << e.what() << std::endl;
            return YAML::Node();
        }
    }

    void VFS::setViewPath(const std::string& viewPath) {
        m_viewPath = viewPath;
        crawlViews();
    }

    void VFS::crawlViews() {
        m_viewRegistry.clear(); // Registry is a std::map<std::string, std::string> in your header

        if (!std::filesystem::exists(m_viewPath) || !std::filesystem::is_directory(m_viewPath)) {
            std::cerr << "[Kito VFS]: Warning - View path does not exist: " << m_viewPath << std::endl;
            return;
        }

        for (const auto& entry : std::filesystem::recursive_directory_iterator(m_viewPath)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                
                // Support both the standard YAML and your custom KML extension
                if (ext == ".yaml" || ext == ".kml") {
                    std::string key = entry.path().stem().string();
                    m_viewRegistry[key] = entry.path().string();
                    
                    std::cout << "[Kito VFS]: Found view '" << key << "' (" << ext << ") at " << entry.path() << std::endl;
                }
            }
        }
    }

    void VFS::crawlModels() {
        m_modelRegistry.clear(); // Registry is a std::map<std::string, std::string> in your header

        if (!std::filesystem::exists(m_modelPath) || !std::filesystem::is_directory(m_modelPath)) {
            std::cerr << "[Kito VFS]: Warning - Model path does not exist: " << m_modelPath << std::endl;
            return;
        }

        for (const auto& entry : std::filesystem::recursive_directory_iterator(m_modelPath)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                
                // Support both the standard YAML and your custom KML extension
                if (ext == ".yaml" || ext == ".kml") {
                    std::string key = entry.path().stem().string();
                    m_modelRegistry[key] = entry.path().string();
                    
                    std::cout << "[Kito VFS]: Found model '" << key << "' (" << ext << ") at " << entry.path() << std::endl;
                }
            }
        }
    }
}