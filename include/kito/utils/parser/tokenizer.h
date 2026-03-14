#pragma once
#include <vector>
#include <string>

namespace kito {

    class Tokenizer {
        public:
            static std::vector<std::string> tokenize(const std::string& str, char delimiter);
    };
}