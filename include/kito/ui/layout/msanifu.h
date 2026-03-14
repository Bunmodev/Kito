#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <kito/ui/widgets/widget.h>
#include <kito/core/window.h>
#include <math.h>
#include <algorithm>

namespace kito::ui {
    class Widget; 
}

namespace kito::layout {

    struct Spacing {
        float left, right, top, bottom = 0;
        float horizontal() const { return left + right; }
        float vertical() const { return top + bottom; }
    };

    struct IntrinsicSize {
        float width = 0;
        float height = 0;
    };

    class Msanifu {
        public:
            Msanifu();
            void applyLayout(const std::vector<SDL_Rect>& widgets);
            void computeLayout(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window);

            void computeMargin(ui::Widget& widget, Window& window);
            // void computeBorder(const ui::Widget& widget);
            void computePadding(ui::Widget& widget, Window& window);
            IntrinsicSize computeGrid(const kito::ui::Widget &widget);

            // 3-step layout computation
            void resolvePass(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window);
            void measurePass(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window);
            void arrangePass(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window);

            void jenga(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window);

    };

}