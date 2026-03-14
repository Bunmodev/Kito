#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <iostream>
#include <string>
#include <kito/core/types.h>


namespace kito {

    class Window
    {

        protected:
            WindowConfig config;

        public:
            Window();
            ~Window();

            void Create(const WindowConfig& config);
            void Destroy();

            bool PollEvents(SDL_Event& event);
            bool IsRunning() const;

            SDL_Renderer* GetRenderer() const;

            float GetMouseX() const { return m_mouseX; }
            float GetMouseY() const { return m_mouseY; }
            bool IsMouseDown() const { return m_mouseDown; }

            int getWidth() const { return config.width; }
            int getHeight() const { return config.height; }

            void setWidth(int width) { config.width = width; }
            void setHeight(int height) { config.height = height; }

            void setRunning(bool running) { m_running = running; }

        private:
            SDL_Window* m_window = nullptr;
            SDL_Renderer* m_renderer = nullptr;

            bool m_running = false;

            float m_mouseX = 0.f;
            float m_mouseY = 0.f;
            bool m_mouseDown = false;
        };
}
