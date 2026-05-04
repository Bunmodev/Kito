#pragma once
#include <memory>
#include <iostream>
#include <windows.h>
#include <kito/mvvm/viewModel.h>
#include <kito/services/vfs.h>

namespace kito::mvvm {
    class ViewModel;
}

namespace kito::services {

    struct ViewModelEntry {
        std::string viewModelPath;
        HINSTANCE dllHandle; // We MUST keep this to unload safely
        mvvm::ViewModel* instance; // Raw pointer because we need custom cleanup
        
        // Custom cleanup to ensure order: 1. Delete Instance -> 2. Unload DLL
        void cleanup() {
            if (instance) {
                // We'll need to call the 'destroy_vm' function from the DLL here
            }
            if (dllHandle) {
                FreeLibrary(dllHandle);
            }
        }
    };

    class ViewModelManager {

        protected:

        public:
            ViewModelManager(const VFS& VFS);
            ~ViewModelManager() = default;

            void loadViewModel(const std::string& name);
            void unloadViewModel(const std::string& name);
            mvvm::ViewModel* getViewModel(const std::string& name);

        private:
            std::unique_ptr<mvvm::ViewModel> m_activeViewModel;
            std::unordered_map<std::string, ViewModelEntry> m_registry;
            VFS& m_vfs;

            typedef mvvm::ViewModel* (*CreateVMFunc)();
            typedef void (*DestroyVMFunc)(mvvm::ViewModel*);

    };
}