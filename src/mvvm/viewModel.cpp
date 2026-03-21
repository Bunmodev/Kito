#include <kito/mvvm/viewModel.h>

namespace kito::mvvm {

    void ViewModel::onClick(std::string id) {
        std::cout << "clicked widget: "<< id << std::endl;
    }
}