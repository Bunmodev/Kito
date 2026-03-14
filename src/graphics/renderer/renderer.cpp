#include <kito/graphics/renderer/renderer.h>

namespace kito::Graphics {

    Renderer::Renderer(SDL_Renderer* sdlRenderer)
        : sdl(sdlRenderer) {}

    void Renderer::clear(uint8_t r, uint8_t g, uint8_t b) {
        SDL_SetRenderDrawColor(sdl, r, g, b, 255);
        SDL_RenderClear(sdl);
    }

    void Renderer::present() {
        SDL_RenderPresent(sdl);
    }

    void Renderer::draw_rect(float x, float y, float w, float h,
                            uint8_t r, uint8_t g, uint8_t b) {
        SDL_FRect rect { x, y, w, h };
        SDL_SetRenderDrawColor(sdl, r, g, b, 255);
        SDL_RenderFillRect(sdl, &rect);
    }

    void Renderer::draw_widgets(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window) {
        layout::Msanifu msanifu;
        style::Nakshi nakshi;

        std::vector<SDL_Rect> widgetRects;

        for (const auto& widget : widgets) {
            if (widget) {
                widgetRects.push_back(widget->getRect());
            }
        }

        // nakshi.bakeStyles(widgets);
        msanifu.computeLayout(widgets, window);

        for (const auto& widget : widgets) {
            if (widget) {
                // This calls Button::draw, which calls Renderer::submit
                widget->draw(*this); 
            }
        }
    }

    void Renderer::draw_widgets_kml(const std::vector<std::unique_ptr<kito::ui::Widget>>& widgets, Window& window) {
        layout::Msanifu msanifu;
        std::vector<SDL_Rect> widgetRects;

        for (const auto& widget : widgets) {
            if (widget) {
                widgetRects.push_back(widget->getRect());
            }

            std::cout << "Widget Rect: (" << widget->getRect().x << ", " << widget->getRect().y << ") size (" << widget->getRect().w << "x" << widget->getRect().h << ")\n";
        }

        msanifu.computeLayout(widgets, window);

        for (const auto& widget : widgets) {
            if (widget) {
                // This calls Button::draw, which calls Renderer::submit
                widget->draw(*this); 
            }
        }
    }

    void Renderer::flush() {
        // Sort commands so lower zIndex (backgrounds) are drawn first
        // std::stable_sort(commands.begin(), commands.end(), [](const DrawCommand& a, const DrawCommand& b) {
        //     return a.zIndex < b.zIndex;
        // });

        for (const auto& cmd : commands) {
            SDL_SetRenderDrawBlendMode(sdl, SDL_BLENDMODE_NONE);
            SDL_SetRenderDrawColor(sdl, cmd.color.r, cmd.color.g, cmd.color.b, cmd.color.a);
            SDL_RenderFillRect(sdl, &cmd.rect);
        }
        
        commands.clear();
    }

    void Renderer::submit(SDL_FRect rect, SDL_Color color, int zIndex) {
        // std::cout << "Submit Rect: " << rect.x << ", " << rect.y << " Size: " << rect.w << "x" << rect.h << "\n";
        commands.push_back({rect, color, zIndex});
    }

}