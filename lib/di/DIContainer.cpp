#include "DIContainer.h"

class DIContainer
{
private:
    std::unordered_map<std::type_index, std::function<void *()>> services;

public:
    template <typename TInterface, typename TImplementation>
    void Register()
    {
        services[typeid(TInterface)] = []() -> void *
        {
            return new TImplementation();
        };
    }

    template <typename TInterface>
    void RegisterInstance(TInterface *instance)
    {
        services[typeid(TInterface)] = [instance]() -> void *
        {
            return instance;
        };
    }

    template <typename TInterface>
    TInterface &Resolve()
    {
        return *reinterpret_cast<TInterface *>(services[typeid(TInterface)]());
    }

    ~DIContainer()
    {
        for (auto &service : services)
        {
            delete reinterpret_cast<void *>(service.second());
        }
    }
};