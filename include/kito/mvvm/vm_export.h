#pragma once
#include <kito/mvvm/viewModel.h>

#define KITO_REGISTER_VM(VM_CLASS) 
extern "C" { 
    __declspec(dllexport) kito::mvvm::ViewModel* create_vm() { 
        return static_cast<kito::mvvm::ViewModel*>(new VM_CLASS()); 
    } 
    __declspec(dllexport) void destroy_vm(kito::mvvm::ViewModel* vm) { 
        delete vm; 
    } 
}