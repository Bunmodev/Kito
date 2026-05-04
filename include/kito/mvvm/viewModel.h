#pragma once
#include <iostream>
#include <string>
// #include <kito/mvvm/vm_export.h>

namespace kito::mvvm {
    
    class ViewModel {
        public:
            ViewModel() = default;
            virtual ~ViewModel() = default;

            virtual void onClick(std::string id) = 0;
    };
}

#define KITO_REGISTER_VM(VM_CLASS) \
extern "C" { \
    __declspec(dllexport) kito::mvvm::ViewModel* create_vm() { \
        return static_cast<kito::mvvm::ViewModel*>(new VM_CLASS()); \
    } \
    __declspec(dllexport) void destroy_vm(kito::mvvm::ViewModel* vm) { \
        delete vm; \
    } \
}


