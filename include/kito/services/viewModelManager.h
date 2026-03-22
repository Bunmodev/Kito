#pragma once
#include <memory>
#include <iostream>
#include <kito/mvvm/viewModel.h>
#include <kito/services/vfs.h>

namespace kito::mvvm {
    class ViewModel;
}

namespace kito::services {

    struct ViewModelEntry {
        std::string viewModelPath;
        std::unique_ptr<mvvm::ViewModel> instance;
    };

    class ViewModelManager {

        protected:

        public:
            ViewModelManager();
            ~ViewModelManager() = default;

            void loadViewModel(const std::string& name);
            void unloadViewModel(const std::string& name);
            mvvm::ViewModel* getViewModel(const std::string& name);

            std::unique_ptr<mvvm::ViewModel> getCurrentView();

        private:
            std::unique_ptr<mvvm::ViewModel> m_activeViewModel;
            std::unordered_map<std::string, ViewModelEntry> m_registry;
            std::unique_ptr<VFS> m_vfs;

    };
}