#pragma once
#include <iostream>
#include <string>

namespace kito::mvvm {
    
    class ViewModel {
        public:
            ViewModel() = default;
            ~ViewModel() = default;

            void onClick(std::string id);
    };
}