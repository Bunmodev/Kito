#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <kito/utils/parser/lexer.h>
#include <kito/ui/core/ui.h>
#include <kito/ui/widgets/widget.h>
#include <kito/utils/parser/token.h>

namespace kito {

    class KMLParser {
        public:
            // return a vector of widgets parsed from the KML file, which can then be passed to the layout system and renderer
            std::vector<std::unique_ptr<kito::ui::Widget>> parseKML(const std::string& filename);

        private:
            // The recursive function that does the actual work
            std::unique_ptr<kito::ui::Widget> parseElement(std::vector<Token>& tokens, int& index);
            
            // Helper to load the file
            std::string loadKML(const std::string& filename);
        };
}
