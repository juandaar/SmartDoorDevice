#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>

class DIContainer {
private:
    std::unordered_map<std::type_index, std::function<void*()>> services;

public: 
    template <typename TInterface, typename TImplementation>
    void Register();

    template <typename TInterface>
    void RegisterInstance(TInterface* instance);

    template <typename TInterface>
    TInterface& Resolve();

    ~DIContainer();
};