#include <kito/ui/core/inflate.h>

namespace kito::ui
{

    std::vector<std::unique_ptr<ui::Widget>> Inflate::inflateYaml(const YAML::Node &yamlView, Window &window)
    {
        std::vector<std::unique_ptr<kito::ui::Widget>> vec;

        // Check if the YAML has a 'widgets' list (or 'children')
        if (yamlView["widgets"] && yamlView["widgets"].IsSequence())
    {
        for (const auto &widgetNode : yamlView["widgets"])
        {
            auto widget = kito::ui_factory::createWidget(widgetNode, window);

            if (widget)
            {
                // --- RECURSION START ---
                // If this widget is a container (or any widget with nested children)
                if (widgetNode["widgets"] && widgetNode["widgets"].IsSequence())
                {
                    // Recurse into this function to get the list of children
                    auto children = inflateYaml(widgetNode, window); 
                    
                    for (auto& child : children)
                    {
                        widget->addChild(std::move(child));
                    }
                }
                // --- RECURSION END ---

                vec.push_back(std::move(widget));
            }
        }
    }
        else
        {
            // Fallback: If it's just one widget at the root, keep your current logic
            auto widget = kito::ui_factory::createWidget(yamlView, window);
            if (widget)
                vec.push_back(std::move(widget));
        }

        return vec;
    };
}
