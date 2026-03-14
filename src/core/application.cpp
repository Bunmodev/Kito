#include <kito/core/application.h>

namespace kito {

    Application::Application(){
        m_window = std::make_unique<Window>();
        m_renderer = nullptr;
        m_configManager = std::make_unique<services::ConfigManager>();
        m_viewManager = std::make_unique<services::ViewManager>();
        m_vfs = std::make_unique<services::VFS>();
    }

    Application::~Application() = default;

    void Application::Init(const std::string& configFile) {
        m_configManager->LoadConfig(configFile);
        auto windowConfig = m_configManager->getWindowConfig();
        m_window->Create(windowConfig);

        // m_vfs->crawlViews();

        auto entry_view = m_vfs->getView("main");
        m_viewManager->loadView("main", entry_view, *m_window);
        
        
        std::cout << "app init sucessfully" << std::endl;
        
        m_renderer = std::make_unique<Graphics::Renderer>(m_window->GetRenderer());

        m_renderer->clear(30, 30, 30);
        m_viewManager->renderView(*m_renderer, *m_window);
        m_renderer->flush();
        m_renderer->present();
    }

    void Application::start() {
        m_running = true;
        
        while (m_window->IsRunning()) {
            SDL_Event event;


            while (m_window->PollEvents(event)) {
                utils::SDLScanner scanner;
                KitoEvent kEvent = scanner.MapToKito(event);
                m_currentEvent = kEvent;

                if (kEvent.type == KitoEvent::Type::Quit) {
                    m_running = false; // The heart stops beating
                    m_window->setRunning(false); // The window closes
                } else {
                    // m_eventQueue.push_back(kEvent);
                    std::cout << "Event: " << static_cast<int>(kEvent.type) << "\n";
                }

                m_renderer->clear(30, 30, 30);
                m_viewManager->renderView(*m_renderer, *m_window);
                m_renderer->flush();
                m_renderer->present();
                m_viewManager->handleEvent(kEvent);
            }

            
        }
    }

}