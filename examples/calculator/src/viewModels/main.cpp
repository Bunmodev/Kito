#include <kito/mvvm/viewModel.h>

class CalculatorViewModel : public kito::mvvm::ViewModel {
public:
    void onClick(std::string id) override {
        if(id == "btn_seven") {

            std::cout << "Calc clicked: " << id << std::endl;
        }
    }
};

// This tells the compiler EXACTLY which class to export.
// No more "expected a type specifier" errors.
KITO_REGISTER_VM(CalculatorViewModel)