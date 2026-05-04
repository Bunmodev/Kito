#include <kito/ui/core/ui.h>

namespace kito::ui_factory {

    std::unique_ptr<kito::ui::Widget> createWidget(const YAML::Node& node, Window& window) {
        std::string type = node["type"].as<std::string>("unknown");
        std::string id = node["id"].as<std::string>(type);

        // int windowWidth = config["window"]["width"].as<int>(800);
        // int windowHeight = config["window"]["height"].as<int>(600);

        // if (config["window"]) {
        //     windowWidth = config["window"]["width"].as<int>(800);
        //     windowHeight = config["window"]["height"].as<int>(600);
        // }

        auto windowWidth = window.getWidth();
        auto windowHeight = window.getHeight();
 
        if (type == "button") {
            
            int x = 0, y = 0, w = 80, h = 50;
            
            
            // Check for the "position" map
            if (node["position"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                int normX = node["position"]["x"].as<int>(0);
                int normY = node["position"]["y"].as<int>(0);

                // replace hardcodded 800x600 with actual window size now that we have it in the config
                 // Default value, should be replaced with actual window size from config
                
                x = normX ;
                y = normY ;
            }

            if (node["size"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                int normW = node["size"]["width"].as<int>(100);
                int normH = node["size"]["height"].as<int>(50);

                w = normW;
                h = normH; 
            }

            auto btn = std::make_unique<kito::ui::Button>(id, x, y, w, h);

            // ! Handle Box Model Properties (margin, border, padding, content)
            // auto asign the size to the content of the widget for now, we can add more complex content handling later
            btn->setContent(w, h);


            if (node["margin"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float left = node["margin"]["left"].as<float>(0.0f);
                float right = node["margin"]["right"].as<float>(0.0f);
                float top = node["margin"]["top"].as<float>(0.0f);
                float bottom = node["margin"]["bottom"].as<float>(0.0f);
                btn->setMargin(left, right, top, bottom);
            } else {
                btn->setMargin(0.0f, 0.0f, 0.0f, 0.0f); // Default to no margin if not specified
            }

            if (node["padding"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float left = node["padding"]["left"].as<float>(0.0f);
                float right = node["padding"]["right"].as<float>(0.0f);
                float top = node["padding"]["top"].as<float>(0.0f);
                float bottom = node["padding"]["bottom"].as<float>(0.0f);
                btn->setPadding(left, right, top, bottom);
            } else {
                btn->setPadding(0.0f, 0.0f, 0.0f, 0.0f); // Default to no padding if not specified
            }

            if (node["border"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float width = node["border"]["width"].as<float>(0.0f);
                btn->setBorder(width, {255, 0, 0, 255}); // Example: Red border with specified width
            } else {
                btn->setBorder(0.0f, {0, 0, 0, 255}); // Default to no border if not specified
            }
            
            return btn;
        }

        if (type == "panel") {
            
            float x = 0, y = 0, w = 100, h = 50;
            
            // Check for the "position" map
            if (node["position"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float normX = node["position"]["x"].as<int>(0.0f);
                float normY = node["position"]["y"].as<int>(0.0f);

                x = normX;
                y = normY;
            }

            if (node["size"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float normW = node["size"]["width"].as<float>(0.0f);
                float normH = node["size"]["height"].as<float>(0.0f);

                w = normW;
                h = normH; 
            }

            auto panel = std::make_unique<kito::ui::Panel>(id, x, y, w, h);

            // ! Handle Box Model Properties (margin, border, padding, content)
            if (node["margin"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float left = node["margin"]["left"].as<float>(0.0f);
                float right = node["margin"]["right"].as<float>(0.0f);
                float top = node["margin"]["top"].as<float>(0.0f);
                float bottom = node["margin"]["bottom"].as<float>(0.0f);
                panel->setMargin(left, right, top, bottom);
            } else {
                panel->setMargin(0.0f, 0.0f, 0.0f, 0.0f); // Default to no margin if not specified
            }
            if(node["padding"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float left = node["padding"]["left"].as<float>(0.0f);
                float right = node["padding"]["right"].as<float>(0.0f);
                float top = node["padding"]["top"].as<float>(0.0f);
                float bottom = node["padding"]["bottom"].as<float>(0.0f);
                panel->setPadding(left, right, top, bottom);
            } else {
                panel->setPadding(0.0f, 0.0f, 0.0f, 0.0f); // Default to no padding if not specified
            }
            if(node["border"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float width = node["border"]["width"].as<float>(0.0f);
                panel->setBorder(width, {255, 0, 0, 255}); // Example: Red border with specified width
            } else {
                panel->setBorder(0.0f, {0, 0, 0, 255}); // Default to no border if not specified
            }
        
            return panel;
        }

        if (type == "container") {
            
            float x = 0, y = 0, w = 100, h = 50;
            
            // Check for the "position" map
            if (node["position"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float normX = node["position"]["x"].as<int>(0.0f);
                float normY = node["position"]["y"].as<int>(0.0f);

                x = normX;
                y = normY;
            }

            if (node["size"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float normW = node["size"]["width"].as<float>(0.0f);
                float normH = node["size"]["height"].as<float>(0.0f);

                w = normW;
                h = normH; 
            }

            auto container = std::make_unique<kito::ui::Container>(id, x, y, w, h);

            // ! Handle Box Model Properties (margin, border, padding, content)
            if (node["margin"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float left = node["margin"]["left"].as<float>(0.0f);
                float right = node["margin"]["right"].as<float>(0.0f);
                float top = node["margin"]["top"].as<float>(0.0f);
                float bottom = node["margin"]["bottom"].as<float>(0.0f);
                container->setMargin(left, right, top, bottom);
            } else {
                container->setMargin(0.0f, 0.0f, 0.0f, 0.0f); // Default to no margin if not specified
            }
            if(node["padding"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float left = node["padding"]["left"].as<float>(0.0f);
                float right = node["padding"]["right"].as<float>(0.0f);
                float top = node["padding"]["top"].as<float>(0.0f);
                float bottom = node["padding"]["bottom"].as<float>(0.0f);
                container->setPadding(left, right, top, bottom);
            } else {
                container->setPadding(0.0f, 0.0f, 0.0f, 0.0f); // Default to no padding if not specified
            }
            if(node["border"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                float width = node["border"]["width"].as<float>(0.0f);
                container->setBorder(width, {255, 0, 0, 255}); // Example: Red border with specified width
            } else {
                container->setBorder(0.0f, {0, 0, 0, 255}); // Default to no border if not specified
            }
            if(node["display"]) {
                // Accessing nested YAML keys: node["parent"]["child"]
                std::string displayType = node["display"].as<std::string>("block");
                container->setDisplay(displayType);
            } else {
                container->setDisplay("block");
            }
        
            return container;
        }

        return nullptr; // Unknown widget type
    }

    // Helper to safely convert string attributes to floats
    float getAttrFloat(const std::vector<std::pair<std::string, std::string>>& attributes, const std::string& key, float defaultVal = 0.0f) {
        for (const auto& attr : attributes) {
            if (attr.first == key) return std::stof(attr.second);
        }
        return defaultVal;
    }

    std::unique_ptr<kito::ui::Widget> createKMLWidget(const std::string& widgetType, const std::vector<std::pair<std::string, std::string>>& attributes) {
        // 1. Common properties for all widgets
        float x = getAttrFloat(attributes, "x");
        float y = getAttrFloat(attributes, "y");
        float w = getAttrFloat(attributes, "width", 100.0f);
        float h = getAttrFloat(attributes, "height", 50.0f);

        std::unique_ptr<kito::ui::Widget> widget = nullptr;

        // 2. Instantiate based on type
        if (widgetType == "button") {
            widget = std::make_unique<kito::ui::Button>("Button", x, y, w, h);
        } else if (widgetType == "panel") {
            widget = std::make_unique<kito::ui::Panel>("Panel", x, y, w, h);
        }

        if (!widget) return nullptr;

        // 3. Apply Box Model (Padding / Margin / Border)
        // KML Style: <button margin-left="10" padding-top="5" border-width="2">
        float mLeft = getAttrFloat(attributes, "margin-left");
        float mRight = getAttrFloat(attributes, "margin-right");
        float mTop = getAttrFloat(attributes, "margin-top");
        float mBottom = getAttrFloat(attributes, "margin-bottom");
        widget->setMargin(mLeft, mRight, mTop, mBottom);

        float pLeft = getAttrFloat(attributes, "padding-left");
        float pRight = getAttrFloat(attributes, "padding-right");
        float pTop = getAttrFloat(attributes, "padding-top");
        float pBottom = getAttrFloat(attributes, "padding-bottom");
        widget->setPadding(pLeft, pRight, pTop, pBottom);

        float bWidth = getAttrFloat(attributes, "border-width");
        widget->setBorder(bWidth, {255, 0, 0, 255}); // Red border for the demo

        widget->setContent(w, h);

        return widget;
    }
}