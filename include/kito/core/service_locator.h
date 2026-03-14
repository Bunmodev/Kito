// kito/core/service_locator.h
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include <iostream>

namespace kito::core {

class ServiceLocator {
public:
    // Register a service: ServiceLocator::provide<VFS>(std::make_shared<VFS>());
    template<typename T>
    static void provide(std::shared_ptr<T> service) {
        services[typeid(T)] = service;
    }

    // Get a service: auto vfs = ServiceLocator::get<VFS>();
    template<typename T>
    static std::shared_ptr<T> get() {
        auto it = services.find(typeid(T));
        if (it != services.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        throw std::runtime_error("Service not found in Kito Registry!");
    }

private:
    // A map that links a "Type" to an "Object"
    static inline std::unordered_map<std::typeindex, std::shared_ptr<void>> services;
};

}