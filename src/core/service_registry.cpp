#include "service_registry.h"

using namespace GTASA::SDK;

ServiceRegistry& ServiceRegistry::instance()
{
	static ServiceRegistry instance;
	return instance;
}

void ServiceRegistry::add(IService* service)
{
	m_services.push_back(std::unique_ptr<IService>(service));
}

const std::vector<std::unique_ptr<IService>>& GTASA::SDK::ServiceRegistry::getAll() const
{
	return m_services;
}

void GTASA::SDK::ServiceRegistry::sort()
{
    std::sort(m_services.begin(), m_services.end(),
        [](const std::unique_ptr<IService>& a,
            const std::unique_ptr<IService>& b)
        {
            return a->Priority() < b->Priority();
        });
}


