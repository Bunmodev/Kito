#pragma once
#include <string>
#include <unordered_map>
#include <any>

namespace kito::mvvm {

    class Model {
        public:
            Model() = default;
            ~Model() = default;

            std::unordered_map<std::string, std::any> properties;

            void setProperty(const std::string& key, const YAML::Node& value) {
                // 1. Check for Boolean
                bool boolVal;
                if (YAML::convert<bool>::decode(value, boolVal)) {
                    properties[key] = boolVal;
                    return;
                }

                // 2. Check for Int
                int intVal;
                if (YAML::convert<int>::decode(value, intVal)) {
                    properties[key] = intVal;
                    return;
                }

                // 3. Check for Float/Double
                float floatVal;
                if (YAML::convert<float>::decode(value, floatVal)) {
                    properties[key] = floatVal;
                    return;
                }

                // 4. Default to String
                properties[key] = value.as<std::string>();
            }

        private:
            std::string m_name;
    };

}