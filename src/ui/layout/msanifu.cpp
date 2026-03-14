#include <kito/ui/layout/msanifu.h>

namespace kito::layout {

    Msanifu::Msanifu() {}

    void Msanifu::applyLayout(const std::vector<SDL_Rect>& widgets) {
        // Placeholder: Just print the widget positions for now
        std::cout << "Applying Msanifu layout to " << widgets.size() << " widgets:\n";
        for (const auto& w : widgets) {
            std::cout << " - Widget at (" << w.x << ", " << w.y << ") size (" << w.w << "x" << w.h << ")\n";
        }
    }

    void Msanifu::computeMargin(ui::Widget& widget, Window& window) {
        auto parent = widget.getParent();
        auto margin = widget.getMargin();
        
        // 1. ALWAYS pull from baseBounds (the static data from YAML)
        auto base = widget.getBaseBounds(); 

        // log out base bounds and margin for debugging
            // std::cout << "Computing margin for widget with base bounds (" << base.x << ", " << base.y << ") size (" << base.width << "x" << base.height << ") and margin (left: " << margin.left << ", right: " << margin.right << ", top: " << margin.top << ", bottom: " << margin.bottom << ")\n";

        if (parent == nullptr) {
            // Compute position relative to the Window (0,0)
            float finalX = base.x + margin.left;
            float finalY = base.y + margin.top;

            // std::cout << "Root widget margin computed: (" << finalX << ", " << finalY << ") size (" << base.width << "x" << base.height << ")\n";

            // 2. ONLY update the computed bounds used for rendering
            widget.updateComputedBounds(finalX, finalY, base.width, base.height);
            return;
        }

        // 3. For children, anchor against the parent's CURRENT computed bounds
        auto parentBounds = parent->getBounds();
        float finalX = parentBounds.x + base.x + margin.left;
        float finalY = parentBounds.y + base.y + margin.top;

        widget.updateComputedBounds(finalX, finalY, base.width, base.height);
    }

    void Msanifu::computePadding(ui::Widget& widget, Window& window) {
        auto padding = widget.getPadding();
        auto outer = widget.getBounds(); // Already computed by computeMargin
        auto content = widget.getContentBounds(); // Start with current content bounds (may be default)

        // The content area is the outer area shifted inwards by padding
        float cx = outer.x + padding.left;
        float cy = outer.y + padding.top;
        float cw = outer.width + (padding.left + padding.right);
        float ch = outer.height + (padding.top + padding.bottom);

        float finalX = outer.x;
        float finalY = outer.y;

        float finalW = cw;
        float finalH = ch;
 
        // Save this so children can access it
        widget.updateContentBounds(cx, cy, cw, ch);
        // widget.updateComputedBounds(finalX, finalY, finalW, finalH); // Ensure computed bounds are updated with padding considered
    }

    IntrinsicSize Msanifu::computeGrid(const kito::ui::Widget &widget) {
        auto& children = widget.getChildren();
        if (children.empty()) {
            auto style = widget.getBakedStyle();
            return { style.padding.left + static_cast<float>(style.padding.right), 
                    style.padding.top + static_cast<float>(style.padding.bottom) };
        }

        auto style = widget.getBakedStyle();
        float maxWidthReached = 0;
        float currentX = style.padding.left;
        float currentY = style.padding.top;
        float rowMaxHeight = 0;
        int colCount = 0;

        auto containerRect = widget.getRect();
        float containerX = containerRect.x;
        float containerY = containerRect.y;
        float boundaryWidth = containerRect.w; 
        

        for(const auto& w : children) {
            auto& rect = w->getRect();
            float wWidth = rect.w;

            // Wrap logic
            bool willOverflow = (currentX + wWidth > boundaryWidth - style.padding.right);
            if (willOverflow && colCount > 0) {
                currentX = style.padding.left;
                currentY += rowMaxHeight + style.grid.rowGap;
                rowMaxHeight = 0;
                colCount = 0;
            }

            maxWidthReached = std::max(maxWidthReached, currentX + wWidth + style.padding.right);
            rowMaxHeight = std::max<float>(rowMaxHeight, static_cast<float>(rect.h));
            currentX += wWidth + style.grid.columnGap;
            colCount++;

            if(colCount >= style.grid.gridCols) {
                currentX = style.padding.left;
                // Only advance Y if we aren't at the very last element to avoid extra gap
                currentY += rowMaxHeight + style.grid.rowGap;
                rowMaxHeight = 0;
                colCount = 0;
            }
        }

        IntrinsicSize maxSizes;
        maxSizes.width = maxWidthReached;
        
        // Final Height: The current Y plus whatever height the last (unwrapped) row had
        maxSizes.height = currentY + rowMaxHeight + style.padding.bottom;

        return maxSizes;
    }

    void Msanifu::resolvePass(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window) {
        // auto parent = widgets.getParent();
        // auto margin = widgets.getMargin();

        // std::cout << "[resolvePass]: resolving layout from styles" << std::endl;
    }

    void Msanifu::measurePass(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window) {
        // 1. DIVE: Handle Nested Measurements first
        // If it has children, they must determine their size BEFORE the parent can.

        for(const auto& widget: widgets) {
            if (!widget->getChildren().empty()) {
                measurePass(widget->getChildren(), window);
            }
  
        

            // 2. SOLVE: Single Measurement / Self Calculation
            // Now that children are measured, this widget can calculate its total footprint.
            
            IntrinsicSize intrinsicSize;

            if (widget->getDisplay().type == "grid") {
                // Grid logic: Sum of children widths/heights + gaps
                intrinsicSize = computeGrid(*widget);
                std::cout << "intrinsicwidth: " << intrinsicSize.width << std::endl;
                std::cout << "intrinsicHeight: " << intrinsicSize.height << std::endl;
                // intrinsicHeight = calculateGridHeight(widget);
            } else {
                // Leaf logic (Button/Text): Just use YAML baseBounds + Nakshi styles
                auto base = widget->getBaseBounds();
                auto style = widget->getBakedStyle(); // From Nakshi
                intrinsicSize.width = base.width + style.padding.left + style.padding.right;
                intrinsicSize.height = base.height + style.padding.top + style.padding.bottom;
            }

            // 3. STORE: Ingrain it in the widget
            widget->setDesiredDimensions(intrinsicSize.width, intrinsicSize.height);
        }
    }

    void Msanifu::arrangePass(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window) {
        for (const auto& widget : widgets) {
            if (widget->getDisplay().type == "grid") {
                auto& children = widget->getChildren();
                auto style = widget->getBakedStyle();
                auto parentRect = widget->getRect(); // Parent is now positioned!

                float curX = style.padding.left;
                float curY = style.padding.top;
                float rowH = 0;
                int count = 0;

                for (const auto& w : children) {
                    auto& r = w->getRect();
                    
                    // Wrap logic again
                    if (curX + r.w > parentRect.w - style.padding.right && count > 0) {
                        curX = style.padding.left;
                        curY += rowH + style.grid.rowGap;
                        rowH = 0;
                        count = 0;
                    }

                    // THE FIX: Parent World Pos + Local Offset
                    w->setRect(parentRect.x + curX, parentRect.y + curY, r.w, r.h);

                    rowH = std::max<float>(rowH, r.h);
                    curX += r.w + style.grid.columnGap;
                    count++;

                    if (count >= style.grid.gridCols) {
                        curX = style.padding.left;
                        curY += rowH + style.grid.rowGap;
                        rowH = 0;
                        count = 0;
                    }
                }  
            } else {
                // FALLBACK: If not a grid, children might just use their absolute baseBounds
                for (const auto& w : widget->getChildren()) {
                    auto base = w->getBaseBounds();
                    auto parentRect = widget->getRect();
                    w->setRect(parentRect.x + base.x, parentRect.y + base.y, base.width, base.height);
                }
            }
            // Recurse down
            if (!widget->getChildren().empty()) {
                arrangePass(widget->getChildren(), window);
            }
        }
    }

    void Msanifu::jenga(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window) {
        resolvePass(widgets, window);
        measurePass(widgets, window);
        arrangePass(widgets, window);
    }

    void Msanifu::computeLayout(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window) {
        jenga(widgets, window);
    }

} 