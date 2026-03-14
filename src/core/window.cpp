#include <kito/core/window.h>

namespace kito {

    Window::Window() {}

    Window::~Window() {
        Destroy();
    }

    void Window::Create(const WindowConfig& config)
    {
        // 1. Initialize Video
        if (!SDL_Init(SDL_INIT_VIDEO)) { 
            std::cout << "SDL Init failed: " << SDL_GetError() << "\n";
            return;
        }

        // 2. Create Window
        // Added SDL_WINDOW_RESIZABLE as an example of a common flag
        // convert title to const char*
        m_window = SDL_CreateWindow(config.title.c_str(), config.width, config.height, SDL_WINDOW_RESIZABLE);
        if (!m_window) {
            std::cout << "Window creation failed: " << SDL_GetError() << "\n";
            return;
        }

        setWidth(config.width);
        setHeight(config.height);

        // 3. Create Renderer
        // Passing nullptr lets SDL3 pick the best hardware driver automatically
        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer) {
            std::cout << "Renderer creation failed: " << SDL_GetError() << "\n";
            return;
        }

        m_running = true;
        std::cout << "Engine Window & Renderer initialized successfully!\n";
    }

    void Window::Destroy()
    {
        if (m_renderer) SDL_DestroyRenderer(m_renderer);
        if (m_window) SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    bool Window::IsRunning() const {
        return m_running;
    }

    SDL_Renderer* Window::GetRenderer() const {
        return m_renderer;
    }

    bool Window::PollEvents(SDL_Event& event) {
        // Check for just ONE event at a time
        if (SDL_PollEvent(&event)) {
            
            // Handle window-specific logic
            if (event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }

            // Keep track of internal state if you still need it
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) m_mouseDown = true;
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)   m_mouseDown = false;

            return true; // We found an event! Hand it to the main loop.
        }
        
        return false; // No more events to process.
    }

}
