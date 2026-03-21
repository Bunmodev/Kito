#include <kito/services/vfs.h>

namespace kito::services {

    VFS::VFS() {
        auto exePath = std::filesystem::current_path();
        m_basePath = std::filesystem::current_path().string();
        m_resourcePath = (m_basePath / "resources.kito");
        

        if (std::filesystem::exists(m_resourcePath)) {
            // Option B: Mount the binary blob
            mount("views/",  m_resourcePath); 
            mount("models/", m_resourcePath);
            m_viewPath = m_resourcePath.string();
            m_modelPath = m_resourcePath.string();
        } else {
            // Option A/Dev: Mount the loose folders
            // We use the same virtual prefix so the rest of the engine doesn't change
            m_viewPath = (std::filesystem::path(m_basePath) / "assets" / "views").string();
            m_modelPath = (std::filesystem::path(m_basePath) / "assets" / "models").string();
            mount("views/",  m_viewPath);
            mount("models/", m_modelPath);
        }
        
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
            auto view = resolve(viewName, "view");
            return view;
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
            auto model = resolve(modelName, "model");
            return model;
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
                    m_viewRegistry[key] = (std::filesystem::path("views") / key);
                    
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

    void VFS::mount(const std::string& virtualPrefix, const std::filesystem::path& physicalPath) {
        m_mountPoints[virtualPrefix] = physicalPath;
    }

    YAML::Node VFS::resolve(const std::string& resourceName, const std::string& resourceType) {
        std::filesystem::path p = resourceName;

        auto folder = p.parent_path().filename().string();
        auto name = p.stem().string();

        std::cout << "views Path: " << m_viewPath << std::endl;

        const std::string t = resourceType; // Lowercase or use a set for efficiency
        if (t == "view" || t == "views" || t == "View" || t == "Views" || t == "VIEW" || t == "VIEWS") {

            if(m_viewPath != m_resourcePath) {
                
                if (!std::filesystem::exists(m_viewPath) || !std::filesystem::is_directory(m_viewPath)) {
                    std::cerr << "[Kito VFS]: Warning - View path does not exist: " << m_viewPath << std::endl;
                    return YAML::Node();
                }

                try {
                    auto it = m_mountPoints.find("views/");

                    if (it != m_mountPoints.end()) {
                        // it->first is the string "views/"
                        // it->second is the std::filesystem::path
                        const std::filesystem::path resolvedViewPath = it->second;
                        auto fullViewPath = (std::filesystem::path(resolvedViewPath) / (resourceName + ".yaml"));
                        std::cout << "[Kito VFS resolve]: successfully resolved resource file - " << fullViewPath << std::endl;

                        return YAML::LoadFile(fullViewPath.string());
                    } else {
                        // Handle the case where "views/" isn't in the map
                        std::cout << "[Kito VFS resolve]: failed to resolve - views wasn't mounted" << resourceName << std::endl;
                    }
                    

                } catch (const YAML::Exception& e) {
                    std::cerr << "[Kito VFS resolve]: YAML Parsing Error in '" << resourceName << "': " << e.what() << std::endl;
                    return YAML::Node();
                }
                        
            }
        }

        if (t == "model" || t == "models" || t == "Model" || t == "Models" || t == "MODEL" || t == "MODELS") {

            if(m_modelPath != m_resourcePath) {
                
                if (!std::filesystem::exists(m_modelPath) || !std::filesystem::is_directory(m_modelPath)) {
                    std::cerr << "[Kito VFS]: Warning - Model path does not exist: " << m_modelPath << std::endl;
                    return YAML::Node();
                }

                try {
                    auto it = m_mountPoints.find("models/");

                    if (it != m_mountPoints.end()) {
                        // it->first is the string "views/"
                        // it->second is the std::filesystem::path
                        const std::filesystem::path resolvedModelPath = it->second;
                        auto fullModelPath = (std::filesystem::path(resolvedModelPath) / (resourceName + ".yaml"));
                        std::cout << "[Kito VFS resolve]: successfully resolved resource file - " << fullModelPath << std::endl;

                        return YAML::LoadFile(fullModelPath.string());
                    } else {
                        // Handle the case where "views/" isn't in the map
                        std::cout << "[Kito VFS resolve]: failed to resolve - model wasn't mounted" << resourceName << std::endl;
                    }
                    

                } catch (const YAML::Exception& e) {
                    std::cerr << "[Kito VFS resolve]: YAML Parsing Error in '" << resourceName << "': " << e.what() << std::endl;
                    return YAML::Node();
                }
                        
            }
        }

        // if(m_mountPoints.find())

        std::cout << "resolving recource folder: " << folder << std::endl;

        return YAML::Node();
    }

}