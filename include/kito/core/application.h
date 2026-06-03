#pragma once
#include <iostream>
#include <kito/core/window.h>
#include <kito/core/events.h>
#include <kito/core/types.h>
#include <kito/graphics/renderer/renderer.h>
#include <kito/utils/helpers/sdl_helper.h>
#include <kito/services/configManager.h>
#include <kito/services/viewManager.h>
#include <kito/services/vfs.h>
#include <memory>
#include <SDL3_ttf/SDL_ttf.h> 


namespace kito {

    namespace utils {
       class SDLScanner;
    }
    
    namespace Graphics {
        class Renderer;
    }

    namespace services {
        class ConfigManager;
        class ViewManager;
        class VFS;
    }

    class Window;

    class Application {
        
        public:
            Application();
            ~Application();

            void Init(const std::string& configFile);
            void start();
            void update();
            void onUpdate();
            void shutdown();

        private:
            std::unique_ptr<Window> m_window;
            std::unique_ptr<Graphics::Renderer> m_renderer;
            std::unique_ptr<services::ConfigManager> m_configManager;
            std::unique_ptr<services::ViewManager> m_viewManager;
            std::unique_ptr<services::VFS> m_vfs;
            
            KitoEvent m_currentEvent;
            bool m_running = false;
            
    };
}