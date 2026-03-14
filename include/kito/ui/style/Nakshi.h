#pragma once 
#include <kito/ui/widgets/widget.h>
#include <kito/utils/parser/configParser.h>

namespace kito::ui {
    class Widget;
};

namespace kito::style {

    class Nakshi {

        public:
            Nakshi() = default;
            ~Nakshi() = default;

            void bakeStyles(const std::vector<std::unique_ptr<ui::Widget>>& widgets);
            void loadStylesFromYaml();
    };

}