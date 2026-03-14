#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <kito/ui/widgets/widget.h>
#include <kito/ui/layout/msanifu.h>
#include <kito/ui/style/Nakshi.h>
#include <kito/core/window.h>


namespace kito {
    class Window; 
}

namespace ui {
    class Widget; 
}

namespace kito::layout {
    class Msanifu;
}

namespace kito::style {
    class Nakshi;
}

namespace kito::Graphics {

    class Renderer {
        struct DrawCommand {
            SDL_FRect rect;
            SDL_Color color;
            int zIndex;
            // SDL_Texture* texture; // Add this later!
        };

        std::vector<DrawCommand> commands;

        public:
            Renderer(SDL_Renderer* sdlRenderer);

            void clear(uint8_t r, uint8_t g, uint8_t b);
            void present();

            void draw_rect(float x, float y, float w, float h,
                        uint8_t r, uint8_t g, uint8_t b);

            void draw_widgets(const std::vector<std::unique_ptr<ui::Widget>>& widgets, Window& window);
            void draw_widgets_kml(const std::vector<std::unique_ptr<ui::Widget>>& widgets, Window& window);

            void submit(SDL_FRect rect, SDL_Color color, int z); // Add to list
            void flush();

        private:
            SDL_Renderer* sdl;
    };

}