#include <kito/services/viewModelManager.h>

namespace kito::services {

    ViewModelManager::ViewModelManager(const VFS& vfs) 
        : m_vfs(const_cast<kito::services::VFS&>(vfs)) {}

    void ViewModelManager::loadViewModel(const std::string& name) {
        // 1. Get the path from our Librarian
        std::filesystem::path binPath = m_vfs.getViewModelPath(name);

        std::cout << "binpath: " << binPath << std::endl;
        
        if (binPath.empty() || !std::filesystem::exists(binPath)) {
            std::cerr << "[Kito VM]: Error - VFS could not find binary for " << name << std::endl;
            return;
        }

        // 2. Windows Handshake
        HINSTANCE hDll = LoadLibraryA(binPath.string().c_str());
        if (!hDll) {
            std::cerr << "[Kito VM]: WinError " << GetLastError() << " loading " << name << std::endl;
            return;
        }

        // 3. Resolve Factory Functions
        auto create_vm = (CreateVMFunc)GetProcAddress(hDll, "create_vm");
        if (!create_vm) {
            std::cerr << "[Kito VM]: " << name << " is not a valid Kito binary (missing create_vm)" << std::endl;
            FreeLibrary(hDll);
            return;
        }

        // 4. Register the logic
        ViewModelEntry entry;
        entry.viewModelPath = binPath.string();
        entry.dllHandle = hDll;
        entry.instance = create_vm(); // Ring the doorbell
        
        m_registry[name] = entry;
        std::cout << "[Kito VM]: Logic linked for view '" << name << "'" << std::endl;
    }

    mvvm::ViewModel* ViewModelManager::getViewModel(const std::string& name) {
        // 1. Check if the VM is actually loaded in our registry
        auto it = m_registry.find(name);
        
        if (it != m_registry.end()) {
            // Return the raw pointer to the living instance
            return it->second.instance;
        }

        // 2. If not found, log it and return nullptr
        // This usually means ViewManager called get before load
        std::cerr << "[Kito VM]: Warning - Requested ViewModel '" << name 
                << "' is not loaded in the registry." << std::endl;
                
        return nullptr;
    }


    void ViewModelManager::unloadViewModel(const std::string& name) {
        if (m_registry.find(name) != m_registry.end()) {
            auto& entry = m_registry[name];
            
            // Find the "Destroyer" inside the DLL before we close the door
            auto destroy_vm = (DestroyVMFunc)GetProcAddress(entry.dllHandle, "destroy_vm");
            if (destroy_vm && entry.instance) {
                destroy_vm(entry.instance);
            }

            FreeLibrary(entry.dllHandle);
            m_registry.erase(name);
        }
    }

} 